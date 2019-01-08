#pragma once

#ifndef _THE_DRIVER_WAGES_H_
#define _THE_DRIVER_WAGES_H_

#define TDW_DEBUG 1                             //debug模式
#define TDW_DEBUG_PRINT_VALUE 1                 //是否输出每分钟收入值
#define TDW_LINE_MAX 200                        //文件每行最大字符数
#define TDW_DEFAULT_DATAS_CAPACITY 10           //tdw_datas默认容量
#define TDW_DEFAULT_DATAS_SET_CAPACITY 10       //tdw_datas_set默认容量
#define TDW_DATAS_CAPACITY_GROWTH 5             //tdw_datas每次扩容增加数量
#define TDW_DATAS_SET_CAPACITY_GROWTH 10        //tdw_datas_set每次扩容增加数量

//重要参数
#define TDW_FUEL_COST_PER_LEN 0.576             //油耗成本(元/每里程)
#define TDW_COST_WITHOUT_FULE_PER_MONTH 3000    //除油耗外成本(元/每月)

//时间
typedef struct _tdw_time {
    int h;
    int m;
}tdw_time;

//时间段
typedef struct _tdw_period {
    tdw_time start, end;
}tdw_period;

//单条数据
typedef struct _tdw_data {
    tdw_period time;
    double len;
    double sum;
}tdw_data;

//多条数据
typedef struct _tdw_datas {
    int count;
    int capacity;
    tdw_data **datas;
}tdw_datas;

//数据集
typedef struct _tdw_datas_set {
    int count;
    int capacity;
    tdw_datas **datas_set;
}tdw_datas_set;

typedef struct _tdw_value {
    int count[1440];//样本数量
    double value[1440];//实际数据
    double fitting_value[1440];//拟合数据
}tdw_value;

//数据操作函数
tdw_datas *tdw_init_datas(int capacity);
tdw_datas *tdw_add_data(tdw_datas *datas, tdw_data *data);
void tdw_free_datas(tdw_datas *datas);

tdw_datas_set *tdw_init_datas_set(int capacity);
tdw_datas_set *tdw_add_datas(tdw_datas_set *datas_set, tdw_datas *datas);
void tdw_free_datas_set(tdw_datas_set *datas_set);

tdw_value *tdw_init_value();

//数据读取函数
tdw_datas *tdw_read_datas_from_file(tdw_datas *datas, const char *path);
tdw_datas_set *tdw_read_datas_set_from_files(tdw_datas_set *datas_set, const char *config_path);

//数据处理函数

//估值函数
void tdw_evaluation_datas(tdw_datas *datas, tdw_value *value);
void tdw_evaluation_datas_set(tdw_datas_set *datas_set, tdw_value *value);

//线性插值
//void linear_interpolation(double *value, double *fitting_value, int count);

//牛顿插值,可以对数据小断层进行修复
void tdw_newton_interpolation(double *value, double *fitting_value, int count);

//数据预测
void tdw_forecast(double *value,int count);

//辅助函数
int tdw_time_to_index(const tdw_time *time);
tdw_time *tdw_index_to_time(int index, tdw_time *time);

#endif // !_THE_DRIVER_WAGES_H_