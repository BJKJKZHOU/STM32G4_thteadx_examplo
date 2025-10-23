/* ----------------------------------------------------------------------
 *  PMSM 电机参数
 * -------------------------------------------------------------------- */
#ifndef PMSM_CONFIG_H
#define PMSM_CONFIG_H

#include <stdint.h>

extern PMSM_Parameters_t g_pmsm_params;

/* 电机参数定义 */
typedef struct {
    /* 基本信息 */
    char model[16];          /* 电机型号 */
    char sn[8];             /* 序列号 */
    
    /* 电气参数 */
    uint8_t pole_pairs;     /* 极对数 */
    float phase_resistance; /* 相电阻 (Ω) */
    float ld_inductance;    /* d轴电感 (H) */
    float lq_inductance;    /* q轴电感 (H) */
    
    /* 机械参数 */
    float inertia;          /* 转动惯量 (kg·m²) */
    float viscous_friction; /* 粘滞摩擦系数 (N·m·s/rad) */
    
    /* 控制参数 */
    float back_emf_const;   /* 反电动势常数 (V/krpm) */
    float torque_const;     /* 转矩常量 (Nm/A) */
    float dc_voltage;       /* 电源电压 (V) */
    
    /* 保护参数 */
    float current_sense_max; /* 电流限制 (A) */
    
    /* 计算参数 */
    float flux_linkage;     /* 永磁链 (Wb) */
    
    /* 校验和 */
    uint16_t checksum;      /* 参数校验和 */
} PMSM_Parameters_t;

#define PMSM_DEFAULT_PARAMS { \
    .model = "lingdong12v", \
    .sn = "001", \
    .pole_pairs = 6, \
    .phase_resistance = 0.0275f, \
    .ld_inductance = 0.000045f, \
    .lq_inductance = 0.000045f, \
    .inertia = 4.56e-5f, \
    .viscous_friction = 2.53e-8f, \
    .back_emf_const = 2.2641f, \
    .torque_const = 0.02647f, \
    .dc_voltage = 12.0f, \
    .current_sense_max = 11.2f, \
    .flux_linkage = 0.0f, /* 将在运行时计算 */ \
    .checksum = 0 \
}








#endif /* PMSM_CONFIG_H */