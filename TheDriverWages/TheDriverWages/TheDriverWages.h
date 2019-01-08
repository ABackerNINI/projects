#pragma once

#ifndef _THE_DRIVER_WAGES_H_
#define _THE_DRIVER_WAGES_H_

#define TDW_DEBUG 1                             //debugģʽ
#define TDW_DEBUG_PRINT_VALUE 1                 //�Ƿ����ÿ��������ֵ
#define TDW_LINE_MAX 200                        //�ļ�ÿ������ַ���
#define TDW_DEFAULT_DATAS_CAPACITY 10           //tdw_datasĬ������
#define TDW_DEFAULT_DATAS_SET_CAPACITY 10       //tdw_datas_setĬ������
#define TDW_DATAS_CAPACITY_GROWTH 5             //tdw_datasÿ��������������
#define TDW_DATAS_SET_CAPACITY_GROWTH 10        //tdw_datas_setÿ��������������

//��Ҫ����
#define TDW_FUEL_COST_PER_LEN 0.576             //�ͺĳɱ�(Ԫ/ÿ���)
#define TDW_COST_WITHOUT_FULE_PER_MONTH 3000    //���ͺ���ɱ�(Ԫ/ÿ��)

//ʱ��
typedef struct _tdw_time {
    int h;
    int m;
}tdw_time;

//ʱ���
typedef struct _tdw_period {
    tdw_time start, end;
}tdw_period;

//��������
typedef struct _tdw_data {
    tdw_period time;
    double len;
    double sum;
}tdw_data;

//��������
typedef struct _tdw_datas {
    int count;
    int capacity;
    tdw_data **datas;
}tdw_datas;

//���ݼ�
typedef struct _tdw_datas_set {
    int count;
    int capacity;
    tdw_datas **datas_set;
}tdw_datas_set;

typedef struct _tdw_value {
    int count[1440];//��������
    double value[1440];//ʵ������
    double fitting_value[1440];//�������
}tdw_value;

//���ݲ�������
tdw_datas *tdw_init_datas(int capacity);
tdw_datas *tdw_add_data(tdw_datas *datas, tdw_data *data);
void tdw_free_datas(tdw_datas *datas);

tdw_datas_set *tdw_init_datas_set(int capacity);
tdw_datas_set *tdw_add_datas(tdw_datas_set *datas_set, tdw_datas *datas);
void tdw_free_datas_set(tdw_datas_set *datas_set);

tdw_value *tdw_init_value();

//���ݶ�ȡ����
tdw_datas *tdw_read_datas_from_file(tdw_datas *datas, const char *path);
tdw_datas_set *tdw_read_datas_set_from_files(tdw_datas_set *datas_set, const char *config_path);

//���ݴ�����

//��ֵ����
void tdw_evaluation_datas(tdw_datas *datas, tdw_value *value);
void tdw_evaluation_datas_set(tdw_datas_set *datas_set, tdw_value *value);

//���Բ�ֵ
//void linear_interpolation(double *value, double *fitting_value, int count);

//ţ�ٲ�ֵ,���Զ�����С�ϲ�����޸�
void tdw_newton_interpolation(double *value, double *fitting_value, int count);

//����Ԥ��
void tdw_forecast(double *value,int count);

//��������
int tdw_time_to_index(const tdw_time *time);
tdw_time *tdw_index_to_time(int index, tdw_time *time);

#endif // !_THE_DRIVER_WAGES_H_