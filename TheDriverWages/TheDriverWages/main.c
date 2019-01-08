#include <stdio.h>
#include <stdlib.h>

#include "TheDriverWages.h"

//默认记录连续且工作时间不超过24小时!
//一个订单称为一条数据.
/*大概思路:
    将一天分割成1440分钟,司机一天的收入=工作时间段内所有分钟收入-除油耗外的成本
    第n分钟收入=第n分钟收入和/覆盖第n分钟的数据条数
    数据d对第n分钟收入的贡献=(d.sum-每里程油耗花费*d.len)/d.time
    数据越多越准确.
    这里有两个不确定因素:
        1.除油耗外的成本
        2.每里程油耗花费
    可以从互联网上获取大概值.
*/

void tdw_period_analysis(double *value) {
    int i;
    tdw_time t1, t2;

    int flag = 0;
    int left_index, right_index;
    for (i = 0; i < 1440; ++i) {
        if (value[i] > -1000) {
            if (flag == 0) {
                left_index = i;
                flag = 1;
            }
        } else {
            if (flag == 1) {
                right_index = i - 1;
                tdw_index_to_time(left_index, &t1);
                tdw_index_to_time(right_index, &t2);
                printf("[%02d:%02d-%02d:%02d]\n", t1.h, t1.m, t2.h, t2.m);
                flag = 0;
            }
        }
    }
    if (flag == 1) {
        right_index = i - 1;
        tdw_index_to_time(left_index, &t1);
        tdw_index_to_time(right_index, &t2);
        printf("[%02d:%02d-%02d:%02d]\n", t1.h, t1.m, t2.h, t2.m);
    }
}

void tdw_calc_and_print(tdw_value *value, tdw_time *t1, tdw_time *t2) {
    int i, left_index, right_index;
    left_index = tdw_time_to_index(t1);
    right_index = tdw_time_to_index(t2);
    double sum = 0;
    if (left_index > right_index) {//跨天
        for (i = left_index; i < 1440; ++i) {
            if (value->fitting_value[i] < -1000) {
                sum = -10000;
                break;
            }
            sum += value->fitting_value[i];
        }
        if (sum > -1000) {
            for (i = 0; i <= right_index; ++i) {
                if (value->fitting_value[i] < -1000) {
                    sum = -10000;
                    break;
                }
                sum += value->fitting_value[i];
            }
        }
    } else {//不跨天
        for (i = left_index; i <= right_index; ++i) {
            if (value->fitting_value[i] < -1000) {
                sum = -10000;
                break;
            }
            sum += value->fitting_value[i];
        }
    }

    if (sum < -1000) {
        printf("范围有误!\n");
    } else {
        printf("若工作时间为[%02d:%02d-%02d:%02d],那么预测该司机:\n", t1->h, t1->m, t2->h, t2->m);
        printf("除油耗后收入为%.2f\n", sum);//暂时未计算除油耗外成本
        printf("除油耗和其它成本(一天)后的收入为%.2f\n", sum - (TDW_COST_WITHOUT_FULE_PER_MONTH / 30.4));//注意这里算的成本为一天
    }
}

void tdw_query(tdw_value *value) {
    int i;

    printf("每里程油耗成本%.2f\n", (double)TDW_FUEL_COST_PER_LEN);
    printf("每月除油耗外成本%.2f\n", (double)TDW_COST_WITHOUT_FULE_PER_MONTH);
    printf("每天除油耗外成本%.2f\n", (double)TDW_COST_WITHOUT_FULE_PER_MONTH / 30.4);
    printf("输入时间段进行查询:格式hh:mm-hh:mm\n");

    double sum;
    tdw_time t1, t2;
    while (scanf("%d:%d-%d:%d", &t1.h, &t1.m, &t2.h, &t2.m) > 0) {
        getchar();

        tdw_calc_and_print(value, &t1, &t2);
    }
}

int main() {
    const char *config_path = "config.txt";
    tdw_datas_set *datas_set = tdw_init_datas_set(TDW_DEFAULT_DATAS_SET_CAPACITY);
    tdw_value *value = tdw_init_value();

    //读取数据
    tdw_read_datas_set_from_files(datas_set, config_path);

    //估值
    tdw_evaluation_datas_set(datas_set, value);

    printf("\n原始数据覆盖时间范围有:\n");
    tdw_period_analysis(value->value);

    //牛顿插值,对数据小断层进行修复
    tdw_newton_interpolation(value->value, value->fitting_value, 1440);

    printf("\n小断层修复后覆盖时间范围有:\n");
    tdw_period_analysis(value->fitting_value);

    //根据已有时间段数据预测未知数据
    //由于数据比较少,难以找到好的预测方法,这里简单的采用均值的方法预测
    tdw_forecast(value->fitting_value, 1440);

    printf("\n均值预测后覆盖时间范围有:\n");
    tdw_period_analysis(value->fitting_value);

#if (TDW_DEBUG&&TDW_DEBUG_PRINT_VALUE)
    int i;
    printf("每分钟收入:\n");
    for (i = 0; i < 1440; ++i) {
        printf("%.2f ", value->value[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    printf("每分钟收入:(牛顿插值后)\n");

    for (i = 0; i < 1440; ++i) {
        printf("%.2f  ", value->fitting_value[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
#endif

    tdw_time t1, t2;
    t1.h = 7;
    t1.m = 0;
    t2.h = 19;
    t2.m = 0;
    tdw_calc_and_print(value, &t1, &t2);

    tdw_query(value);

    tdw_free_datas_set(datas_set);
    free(value);

    return 0;
}