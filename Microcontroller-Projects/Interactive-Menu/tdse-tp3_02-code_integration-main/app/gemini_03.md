# Análisis de board.h, dwt.h y systick.c

## **1. board.h - Sistema de Abstracción de Hardware**

### **Propósito Principal:**
Abstraer las diferencias entre diferentes placas de desarrollo STM32 mediante definiciones condicionales.

### **Estructura del Archivo:**

#### **Definición de Placas Soportadas:**
```c
#define NUCLEO_F103RC    (0)
#define NUCLEO_F303R8    (1)
// ... más placas
#define BOARD (NUCLEO_F103RC)  // Placa actual seleccionada
```

#### **Configuración por Tipo de Placa:**

**Placas de 64 pines (NUCLEO_F103RC, F401RE, F446RE):**
```c
#define BTN_A_PIN        B1_Pin
#define BTN_A_PORT       B1_GPIO_Port
#define BTN_A_PRESSED    GPIO_PIN_RESET  // Botón activo en LOW
#define BTN_A_HOVER      GPIO_PIN_SET

#define LED_A_PIN        LD2_Pin
#define LED_A_PORT       LD2_GPIO_Port  
#define LED_A_ON         GPIO_PIN_SET    // LED activo en HIGH
#define LED_A_OFF        GPIO_PIN_RESET
```

**Características:**
- **Botón**: Configurado como activo en bajo (`GPIO_PIN_RESET`)
- **LED**: Configurado como activo en alto (`GPIO_PIN_SET`)
- **Puertos**: Usa definiciones generadas por STM32CubeMX

### **Ventajas de esta Abstracción:**
- **Portabilidad**: Cambiar de placa solo requiere modificar `#define BOARD`
- **Consistencia**: Mismos nombres de macros en todas las placas
- **Mantenibilidad**: Configuración centralizada

## **2. dwt.h - Sistema de Medición de Ciclos de CPU**

### **Propósito:**
Utilizar el **Data Watchpoint and Trace (DWT)** unit de ARM Cortex-M para medición precisa de tiempo a nivel de ciclos de CPU.

### **Características Técnicas:**

#### **Inicialización del Contador:**
```c
static inline void cycle_counter_init(void)
{
     CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;  // Habilita DWT
     DWT->CYCCNT = 0;                                 // Resetea contador
     DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            // Inicia conteo
}
```

#### **Funciones Principales:**
- `cycle_counter_init()`: Habilita el hardware DWT
- `cycle_counter_reset()`: Pone el contador a cero
- `cycle_counter_get()`: Lee ciclos transcurridos
- `cycle_counter_get_time_us()`: Convierte ciclos a microsegundos

### **Cálculo de Tiempo:**
```c
static inline uint32_t cycle_counter_get_time_us(void)
{
    return (DWT->CYCCNT / (SystemCoreClock / 1000000));
}
```
**Fórmula**: `microsegundos = ciclos / (frecuencia_CPU / 1,000,000)`

### **Precisión:**
- **Resolución**: 1 ciclo de CPU
- **Ejemplo**: Si `SystemCoreClock = 72 MHz`, resolución = 13.89 ns
- **Overhead**: Mínimo (funciones inline)

## **3. systick.c - Sistema de Delay de Alta Precisión**

### **Propósito:**
Implementar delays en microsegundos usando el timer SysTick del Cortex-M.

### **Algoritmo de Delay:**
```c
void systick_delay_us(uint32_t delay_us)
{
    uint32_t start, current, target, elapsed;
    
    // Calcula ciclos objetivo
    target = delay_us * (SystemCoreClock / 1000000UL);
    
    start = SysTick->VAL;
    
    while (1) {
        current = SysTick->VAL;
        
        // Maneja wraparound del contador
        if (current <= start) {
            elapsed = start - current;
        } else {
            elapsed = SysTick->LOAD + start - current;
        }
        
        if (elapsed >= target) break;
    }
}
```

### **Características del Algoritmo:**

#### **1. Cálculo de Target:**
```c
target = delay_us * (SystemCoreClock / 1000000UL);
```
- Convierte microsegundos a ciclos de reloj
- Ejemplo: 100μs @ 72MHz = 100 × 72 = 7200 ciclos

#### **2. Manejo de Wraparound:**
El contador SysTick decrementa y se recarga, por lo que debe manejarse el desbordamiento.

#### **3. Precisión:**
- **No-blocking relativo**: Usa tiempo transcurrido, no absoluto
- **Independiente de carga del sistema**: Más preciso que delays basados en loops

## **Integración en el Sistema Global**

### **Relación con las Variables de Tiempo:**

#### **g_app_runtime_us:**
- **Origen**: `cycle_counter_get_time_us()` en `app_update()`
- **Precisión**: Basada en DWT (ciclos de CPU)
- **Impacto**: Mide EXACTAMENTE el tiempo de ejecución de tareas

#### **task_dta_list[index].WCET:**
- **Origen**: Máximo de `cycle_counter_get_time_us()`
- **Utilidad**: Análisis de peor caso de ejecución
- **Precisión**: Nivel de ciclos de CPU

#### **g_task_test_tick_cnt:**
- **Origen**: Interrupciones SysTick (1ms)
- **Relación**: `systick_delay_us()` usa el mismo hardware pero de manera diferente

### **Diferencias entre Sistemas de Tiempo:**

| Sistema | Resolución | Propósito | Overhead |
|---------|------------|-----------|----------|
| **DWT** | Ciclos CPU | Medición performance | Mínimo |
| **SysTick Delay** | ~1μs | Delays precisos | Medio |
| **SysTick Interrupt** | 1ms | Scheduling | Bajo |

### **Ejemplo de Uso Integrado:**

```c
// En app_update():
cycle_counter_reset();                          // Reset DWT
(*task_cfg_list[index].task_update)(...);       // Ejecuta tarea
cycle_counter_time_us = cycle_counter_get_time_us();  // Mide con DWT

// En display.c:
systick_delay_us(50);  // Delay preciso para inicialización LCD
```

## **Impacto en el Rendimiento del Sistema**

### **Ventajas:**
1. **Medición precisa** del tiempo de ejecución real
2. **Delays confiables** para periféricos (LCD)
3. **Abstracción de hardware** para portabilidad
4. **Bajo overhead** en operación normal

### **Consideraciones:**
- **DWT**: No disponible en todos los Cortex-M
- **SysTick Delay**: Ocupa CPU (blocking)
- **Precisión**: Depende de la estabilidad del clock del sistema

**Estos módulos forman la base del sistema de medición y control de tiempo que permite el análisis preciso de performance en el sistema embebido.**