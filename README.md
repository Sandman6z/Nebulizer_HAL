# Nebulizer HAL by STM32
- [PCB Project](https://github.com/Sandman6z/Nebulizer_Medical_PCB)
---
### 雾化参数
- 雾化率： ≥0.25mL/min best:0.35mL/min
- 震荡频率： 120kHz ±10%
- 噪声： ≤20dB（A计权）
- 残液量： ≤0.15mL
- 粒径： 3.7μm ±25% 小于5μm的≥60%
---
### 电气参数：
- V采样电阻max p-p = 740mV
- V杯空但连接max = 64V
- V杯未连接max = 180V

---

> STM32C031 -> STM32G031 change
  1. PWM Generation:`TIM1 CH3 -> TIM1 CH1`
  2. PWM Output:`TIM3 CH1 -> TIM2 CH1`
  3. PWM Input: `TIM3 CH3 -> TIM2 CH2`
  4. 