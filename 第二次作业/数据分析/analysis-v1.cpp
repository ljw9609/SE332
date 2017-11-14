//
//  main.cpp
//  petri_data_analysis
//
//  Created by 吕嘉伟 on 2017/11/11.
//  Copyright © 2017年 吕嘉伟. All rights reserved.
//

#include <iostream>
#include <stdio.h>
using namespace std;

#define STU_NUM  40
#define REGISTER 1
#define COUR1    1
#define REVERSE  14
#define COUR2    21
#define COUR3    7
#define EXAM     1
#define CERT     3
#define REFUND   3
#define TUITION  9000
#define COACH    6;

int main(int argc, const char * argv[]) {
    if(argc != 2){
        cout << "argument error!" << endl;
        exit(1);
    }

    /* 读取行数 */
    FILE* tmp_file = fopen(argv[1], "r");
    if(!tmp_file){
        cout << "open file error!" << endl;
        exit(1);
    }
    int cnt = 0;
    char tmp_char;
    while((tmp_char = fgetc(tmp_file)) != EOF){
        if(tmp_char == '\n')
            cnt ++;
    }
    fclose(tmp_file);
    
    /* 读入数据 */
    FILE* file = fopen(argv[1], "r");
    int fail_cour1[cnt];
    int fail_rever[cnt];
    int fail_cour2[cnt];
    int fail_cour3_1[cnt];
    int fail_cour3_2[cnt];
    int fail_cour3_3[cnt];
    int fail_cour3_4[cnt];
    int fail_cour3_5[cnt];
    int fail_cour3[cnt];
    int pass[cnt];
    int fail[cnt];
    
    int a,b,c,d,e,f,u,v,x,y;
    for(int i = 0;i < cnt;i++){
        fscanf(file,"%d %d %d %d %d %d %d %d %d %d\n",&a,&b,&c,&d,&e,&f,&u,&v,&x,&y);
        fail_cour1[i] = a;
        fail_rever[i] = b;
        fail_cour2[i] = c;
        fail_cour3_1[i] = d;
        fail_cour3_2[i] = e;
        fail_cour3_3[i] = f;
        fail_cour3_4[i] = u;
        fail_cour3_5[i] = v;
        fail_cour3[i] = d + e + f + u + v;
        pass[i] = x;
        fail[i] = y;
    }
    fclose(file);

    /* 计算数据 */
    double total_time;
    double teach_time;
    int total_pass = 0;
    
    total_time = cnt * STU_NUM * (REGISTER + COUR1 + COUR2 + COUR3 + REVERSE + EXAM * 4 + CERT);
    teach_time = cnt * STU_NUM * (COUR2 + COUR3 + REVERSE);
    for(int i = 0;i < cnt;i++){
        total_time = total_time + fail_cour1[i] * (COUR1 + EXAM) + fail_rever[i] * (REVERSE + EXAM) +
    fail_cour2[i] * (COUR2 + EXAM) + fail_cour3[i] * (COUR3 + EXAM); 
        teach_time = teach_time + fail_cour2[i] * COUR2 + 
    fail_cour3[i] * COUR3 + fail_rever[i] * REVERSE;
    	total_pass += pass[i];
    }
    
    
    double avg_total_time;
    double avg_teach_time;
    double avg_passing_rate;
    int max_student;
    int gross_income;
    avg_total_time = total_time / (STU_NUM * cnt);
    avg_teach_time = teach_time / (STU_NUM * cnt);
    avg_passing_rate = (double)total_pass / (STU_NUM * cnt) * 100;
    max_student = (int)(365.0 / avg_teach_time) * COACH;
    gross_income = max_student * TUITION;
    
    cout << "模拟次数：" << cnt << endl;
    cout << "平均完成时间：" << avg_total_time << "天" << endl;
    cout << "平均教学时间：" << avg_teach_time << "天" << endl;
    cout << "平均通过率：" << avg_passing_rate << "%" << endl;
    cout << "每年最多可招收学生数：" << max_student << "个" << endl;
    cout << "每年毛收入：" << gross_income << "元" << endl;
    
    return 0;
}
