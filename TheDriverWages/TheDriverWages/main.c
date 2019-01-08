#include <stdio.h>
#include <stdlib.h>

#include "TheDriverWages.h"

//Ĭ�ϼ�¼�����ҹ���ʱ�䲻����24Сʱ!
//һ��������Ϊһ������.
/*���˼·:
    ��һ��ָ��1440����,˾��һ�������=����ʱ��������з�������-���ͺ���ĳɱ�
    ��n��������=��n���������/���ǵ�n���ӵ���������
    ����d�Ե�n��������Ĺ���=(d.sum-ÿ����ͺĻ���*d.len)/d.time
    ����Խ��Խ׼ȷ.
    ������������ȷ������:
        1.���ͺ���ĳɱ�
        2.ÿ����ͺĻ���
    ���Դӻ������ϻ�ȡ���ֵ.
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
    if (left_index > right_index) {//����
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
    } else {//������
        for (i = left_index; i <= right_index; ++i) {
            if (value->fitting_value[i] < -1000) {
                sum = -10000;
                break;
            }
            sum += value->fitting_value[i];
        }
    }

    if (sum < -1000) {
        printf("��Χ����!\n");
    } else {
        printf("������ʱ��Ϊ[%02d:%02d-%02d:%02d],��ôԤ���˾��:\n", t1->h, t1->m, t2->h, t2->m);
        printf("���ͺĺ�����Ϊ%.2f\n", sum);//��ʱδ������ͺ���ɱ�
        printf("���ͺĺ������ɱ�(һ��)�������Ϊ%.2f\n", sum - (TDW_COST_WITHOUT_FULE_PER_MONTH / 30.4));//ע��������ĳɱ�Ϊһ��
    }
}

void tdw_query(tdw_value *value) {
    int i;

    printf("ÿ����ͺĳɱ�%.2f\n", (double)TDW_FUEL_COST_PER_LEN);
    printf("ÿ�³��ͺ���ɱ�%.2f\n", (double)TDW_COST_WITHOUT_FULE_PER_MONTH);
    printf("ÿ����ͺ���ɱ�%.2f\n", (double)TDW_COST_WITHOUT_FULE_PER_MONTH / 30.4);
    printf("����ʱ��ν��в�ѯ:��ʽhh:mm-hh:mm\n");

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

    //��ȡ����
    tdw_read_datas_set_from_files(datas_set, config_path);

    //��ֵ
    tdw_evaluation_datas_set(datas_set, value);

    printf("\nԭʼ���ݸ���ʱ�䷶Χ��:\n");
    tdw_period_analysis(value->value);

    //ţ�ٲ�ֵ,������С�ϲ�����޸�
    tdw_newton_interpolation(value->value, value->fitting_value, 1440);

    printf("\nС�ϲ��޸��󸲸�ʱ�䷶Χ��:\n");
    tdw_period_analysis(value->fitting_value);

    //��������ʱ�������Ԥ��δ֪����
    //�������ݱȽ���,�����ҵ��õ�Ԥ�ⷽ��,����򵥵Ĳ��þ�ֵ�ķ���Ԥ��
    tdw_forecast(value->fitting_value, 1440);

    printf("\n��ֵԤ��󸲸�ʱ�䷶Χ��:\n");
    tdw_period_analysis(value->fitting_value);

#if (TDW_DEBUG&&TDW_DEBUG_PRINT_VALUE)
    int i;
    printf("ÿ��������:\n");
    for (i = 0; i < 1440; ++i) {
        printf("%.2f ", value->value[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    printf("ÿ��������:(ţ�ٲ�ֵ��)\n");

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