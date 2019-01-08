#include "TheDriverWages.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tdw_datas *tdw_init_datas(int capacity) {
    tdw_datas *datas = (tdw_datas *)malloc(sizeof(tdw_datas));
    datas->capacity = capacity;
    datas->count = 0;
    datas->datas = (tdw_data **)malloc(sizeof(tdw_data*)*capacity);

    return datas;
}

tdw_datas *tdw_add_data(tdw_datas *datas, tdw_data *data) {
    if (datas->count == datas->capacity) {
        datas->capacity += TDW_DATAS_CAPACITY_GROWTH;
        datas->datas = (tdw_data **)realloc(datas->datas, sizeof(tdw_data*)*datas->capacity);
    }
    datas->datas[datas->count++] = data;

    return datas;
}

void tdw_free_datas(tdw_datas *datas) {
    int i;
    for (i = 0; i < datas->count; ++i)
        free(datas->datas[i]);

    free(datas->datas);
    free(datas);
}

tdw_datas_set *tdw_init_datas_set(int capacity) {
    tdw_datas_set *datas_set = (tdw_datas_set *)malloc(sizeof(tdw_datas_set));
    datas_set->capacity = capacity;
    datas_set->count = 0;
    datas_set->datas_set = (tdw_datas **)malloc(sizeof(tdw_datas*)*capacity);

    return datas_set;
}

tdw_datas_set *tdw_add_datas(tdw_datas_set *datas_set, tdw_datas *datas) {
    if (datas_set->count == datas_set->capacity) {
        datas_set->capacity += TDW_DATAS_SET_CAPACITY_GROWTH;
        datas_set->datas_set = (tdw_datas **)malloc(sizeof(tdw_datas*)*datas_set->capacity);
    }
    datas_set->datas_set[datas_set->count++] = datas;

    return datas_set;
}

void tdw_free_datas_set(tdw_datas_set *datas_set) {
    int i;
    for (i = 0; i < datas_set->count; ++i)
        tdw_free_datas(datas_set->datas_set[i]);

    free(datas_set->datas_set);
    free(datas_set);
}

tdw_value *tdw_init_value() {
    tdw_value *value = (tdw_value *)malloc(sizeof(tdw_value));
    int i;
    for (i = 0; i < 1440; ++i) {
        value->count[i] = 0;
        value->value[i] = -10000.0;
        value->fitting_value[i] = -10000.0;
    }

    return value;
}

tdw_datas *tdw_read_datas_from_file(tdw_datas *datas, const char *path) {
    FILE *file = fopen(path, "r");
    //TODO ERROR HANDLE
    tdw_data *data = NULL;
    char line[TDW_LINE_MAX];
    int num, order = 1;
    char dot, c;
    while (fscanf(file, "%[^\n]", line) != EOF) {
        c = fgetc(file);
        sscanf(line, "%d%c", &num, &dot);
        if (num == order && dot == '.') {
            data = (tdw_data*)malloc(sizeof(tdw_data));
            fscanf(file, "time:%d:%d-%d:%d%[^\n]", &data->time.start.h, &data->time.start.m, &data->time.end.h, &data->time.end.m, line);
            c = fgetc(file);
            fscanf(file, "len:%lf%[^\n]", &data->len, line);
            c = fgetc(file);
            fscanf(file, "sum:%lf%[^\n]", &data->sum, line);
            c = fgetc(file);
            //fgets(line, TDW_LINE_MAX, file);
            tdw_add_data(datas, data);
            ++order;
        }
    }

#if TDW_DEBUG
    printf("[debug]path:[%s] datas count:[%d] capacity:[%d]@tdw_read_datas_from_file\n", path, datas->count, datas->capacity);
#endif

    fclose(file);

    return datas;
}

tdw_datas_set *tdw_read_datas_set_from_files(tdw_datas_set *datas_set, const char *config_path) {
    FILE *file = fopen(config_path, "r");
    //TODO ERROR HANDLE
    char path[FILENAME_MAX];
    tdw_datas *datas = NULL;
    while (fscanf(file, "%s\n", path) == 1) {
        datas = tdw_init_datas(TDW_DEFAULT_DATAS_CAPACITY);
        tdw_read_datas_from_file(datas, path);
        tdw_add_datas(datas_set, datas);
    }

#if TDW_DEBUG
    printf("[debug]config path:[%s] files count:[%d] capacity:[%d]@tdw_read_datas_set_from_files\n", config_path, datas_set->count, datas_set->capacity);
#endif

    fclose(file);

    return datas_set;
}

void tdw_evaluation_datas(tdw_datas *datas, tdw_value *value) {
    int index_begin = tdw_time_to_index(&datas->datas[0]->time.start);
    int index_end = tdw_time_to_index(&datas->datas[datas->count - 1]->time.end);
    if (index_begin > index_end) {//跨天
        for (; index_begin < 1440; ++index_begin) {
            ++(value->count[index_begin]);
            if (value->value[index_begin] < -1000) {
                value->value[index_begin] = 0;
            }
        }
        for (index_begin = 0; index_begin < index_end; ++index_begin) {
            ++(value->count[index_begin]);
            if (value->value[index_begin] < -1000) {
                value->value[index_begin] = 0;
            }
        }
    } else {//不跨天
        for (; index_begin < index_end; ++index_begin) {
            ++(value->count[index_begin]);
            if (value->value[index_begin] < -1000) {
                value->value[index_begin] = 0;
            }
        }
    }

    int i;
    double average;
    for (i = 0; i < datas->count; ++i) {
        index_begin = tdw_time_to_index(&datas->datas[i]->time.start);
        index_end = tdw_time_to_index(&datas->datas[i]->time.end);
        if (index_begin > index_end) {//跨天
            average = (datas->datas[i]->sum - TDW_FUEL_COST_PER_LEN * datas->datas[i]->len) / (1440 - (index_begin - index_end));
            for (; index_begin < 1440; ++index_begin) {
                value->value[index_begin] += average;
            }
            for (index_begin = 0; index_begin < index_end; ++index_begin) {
                value->value[index_begin] += average;
            }
        } else {//不跨天
            average = (datas->datas[i]->sum - TDW_FUEL_COST_PER_LEN * datas->datas[i]->len) / (index_end - index_begin);
            for (; index_begin < index_end; ++index_begin) {
                value->value[index_begin] += average;
            }
        }
    }
}

void tdw_evaluation_datas_set(tdw_datas_set *datas_set, tdw_value *value) {
    int i;
    for (i = 0; i < datas_set->count; ++i) {
        tdw_evaluation_datas(datas_set->datas_set[i], value);
    }

    for (i = 0; i < 1440; ++i) {
        if (value->count[i] != 0) {// != 0
            value->value[i] /= value->count[i];
        }
    }
}

//void linear_interpolation(double *value, double *fitting_value, int count) {
//    int i, left_index, right_index;
//    double left_value, right_value;
//    for (i = 0; i < count; ++i) {
//        if (value[i] == -1.0) {
//
//        }
//    }
//}

void tdw_newton_interpolation(double *value, double *fitting_value, int count) {
    double *x = (double *)malloc(sizeof(double)*(7));
    double *y = (double *)malloc(sizeof(double)*(7));
    double *form = (double *)malloc(sizeof(double)*(7));
    int i, j, k, pcnt = 0;

    for (i = 0; i < count; ++i) {
        if (value[i] < -1000) {// == -1
            pcnt = 0;
            //左边找3个值
            for (j = i - 1, k = 2; j >= 0 && k >= 0; --j) {
                if (value[j] > -1000) {
                    x[k] = j;
                    y[k--] = value[j];
                    ++pcnt;
                }
            }
            //右边找3个值
            for (j = i + 1, k = 3; j < count&&k < 6; ++j) {
                if (value[j] > -1000) {
                    x[k] = j;
                    y[k++] = value[j];
                    ++pcnt;
                }
            }

            if (pcnt < 6) {
                continue;
            }

            //对差商表进行初始化
            for (j = 0; j < pcnt; ++j)
                form[j] = y[j];
            for (j = 0; j < pcnt; ++j) {
                for (k = pcnt; k > j; --k) {
                    //差商的计算，f(X0,X1,X2,X3...Xn)的值 
                    form[k] = (form[k] - form[k - 1]) / (x[k] - x[k - 1 - j]);
                }
            }

            double tmp, newton;
            tmp = 1;
            newton = form[0];
            for (j = 0; j < pcnt; j++) {
                //根据牛顿插值公式，上面差商表都计算完毕了，现在吧差商乘以牛顿插值函数，全部加起来就OK了 
                tmp = tmp * (i - x[j]);//tmp是插值函数:例如（x-x0),(x-x1),(x-x2)等
                newton = newton + tmp * form[j + 1];//完成后newton就是f(x)的值了
            }
            fitting_value[i] = newton;
        } else {
            fitting_value[i] = value[i];
        }
    }

    free(x);
    free(y);
    free(form);
}

void tdw_forecast(double *value, int count) {
    int i;
    tdw_time t1, t2;

    //找到最大已知时间段
    int flag = 0;
    int left_index, right_index, l_tmp = 0, r_tmp = 0, max_gap = 0;
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
                if (right_index - left_index > max_gap) {
                    l_tmp = left_index;
                    r_tmp = right_index;
                    max_gap = right_index - left_index;
                }
                //printf("[%02d:%02d-%02d:%02d]\n", t1.h, t1.m, t2.h, t2.m);
                flag = 0;
            }
        }
    }
    if (flag == 1) {
        right_index = i - 1;
        tdw_index_to_time(left_index, &t1);
        tdw_index_to_time(right_index, &t2);
        if (right_index - left_index > max_gap) {
            l_tmp = left_index;
            r_tmp = right_index;
            max_gap = right_index - left_index;
        }
        //printf("[%02d:%02d-%02d:%02d]\n", t1.h, t1.m, t2.h, t2.m);
    }

    //计算平均值,并填充未知时间
    double sum = 0;
    for (i = left_index; i <= right_index; ++i) {
        sum += value[i];
    }
    double average = sum / (right_index - left_index);
    for (i = 0; i < 1440; ++i) {
        if (value[i] < -1000) {
            value[i] = average;
        }
    }
}

int tdw_time_to_index(const tdw_time *time) {
    return time->h >= 24 ? (time->h - 24) * 60 + time->m : time->h * 60 + time->m;
}

tdw_time *tdw_index_to_time(int index, tdw_time *time) {
    time->h = index / 60;
    time->m = index % 60;

    return time;
}