## Análisis del Sistema Embebido Completo

### **Arquitectura General del Sistema**

Este es un sistema embebido **Bare Metal - Event-Triggered Systems (ETS)** que utiliza **STM32CubeMX** con **HAL** y sigue una arquitectura basada en tareas.

### **Flujo de Ejecución Principal**

#### **1. Inicialización (`main.c` → `app_init()`)**
```c
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    app_init();        // ← INICIALIZACIÓN
    while (1) {
        app_update();  // ← LOOP PRINCIPAL
    }
}
```

#### **2. Gestión de Tiempo - SysTick**
- **Frecuencia**: 1 kHz (1 ms por tick)
- **Handler**: `SysTick_Handler()` en `stm32f1xx_it.c`
- **Callback**: `HAL_SYSTICK_Callback()` en `app.c`

### **Evolución de las Variables Clave**

#### **Variable 1: `g_app_runtime_us`**
- **Unidad**: Microsegundos (μs)
- **Propósito**: Tiempo total de ejecución de todas las tareas en un ciclo

```c
// En app_update():
g_app_runtime_us = 0;
for (index = 0; TASK_QTY > index; index++) {
    cycle_counter_reset();
    (*task_cfg_list[index].task_update)(...);
    cycle_counter_time_us = cycle_counter_get_time_us();
    g_app_runtime_us += cycle_counter_time_us;  // ← ACUMULA TIEMPO
}
```

**Evolución**:
- **Inicio**: No inicializada explícitamente (probablemente 0)
- **Cada `app_update()`**:
  - Se resetea a 0 al inicio del ciclo
  - Se incrementa con el tiempo de ejecución de cada tarea
  - Representa el **tiempo total de CPU** usado por todas las tareas

#### **Variable 2: `task_dta_list[index].WCET`**
- **Unidad**: Microsegundos (μs)
- **Propósito**: Worst-Case Execution Time - Tiempo máximo de ejecución histórico

```c
// En app_update():
if (task_dta_list[index].WCET < cycle_counter_time_us) {
    task_dta_list[index].WCET = cycle_counter_time_us;  // ← ACTUALIZA MÁXIMO
}
```

**Evolución**:
- **Inicio**: `TASK_X_WCET_INI` = 0 (en `app_init()`)
- **Cada `app_update()`**:
  - Se compara con el tiempo actual de ejecución
  - Solo se actualiza si el tiempo actual es **MAYOR** que el histórico
  - Almacena el **peor caso de tiempo de ejecución** de cada tarea

#### **Variable 3: `g_task_test_tick_cnt`**
- **Unidad**: Ticks del sistema (1 tick = 1 ms)
- **Propósito**: Contador de ticks para la tarea de prueba

```c
// En stm32f1xx_it.c (SysTick_Handler):
void SysTick_Handler(void) {
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

// En app.c (callback):
void HAL_SYSTICK_Callback(void) {
    g_app_tick_cnt++;
    g_task_test_tick_cnt++;  // ← INCREMENTA CADA 1ms
}
```

**Evolución**:
- **Inicio**: `G_APP_TICK_CNT_INI` = 0 (en `app_init()`)
- **Cada 1 ms**: Se incrementa en la interrupción SysTick
- **En `task_test_update()`**: Se decrementa hasta llegar a 0

### **Comportamiento Detallado del Sistema**

#### **Secuencia de Inicialización:**
1. `main()` → `app_init()`
2. `app_init()` → `task_test_init()`
3. `task_test_init()` → `displayInit(DISPLAY_CONNECTION_GPIO_4BITS)`
4. Se inicializan contadores a 0

#### **Loop Principal (`app_update()`):**
```c
void app_update(void) {
    while (g_app_tick_cnt > 0) {  // Ejecuta por cada tick acumulado
        g_app_cnt++;
        g_app_runtime_us = 0;
        
        for (cada tarea) {
            // Mide tiempo de ejecución
            cycle_counter_reset();
            task_test_update();
            tiempo = cycle_counter_get_time_us();
            
            // Actualiza estadísticas
            g_app_runtime_us += tiempo;
            if (WCET < tiempo) WCET = tiempo;
        }
        
        g_app_tick_cnt--;  // Consume un tick
    }
}
```

#### **Tarea de Test (`task_test_update()`):**
```c
void task_test_update(void) {
    while (g_task_test_tick_cnt > 0) {
        g_task_test_cnt++;
        task_test_statechart();
        g_task_test_tick_cnt--;  // Consume ticks de test
    }
}
```

### **Ejemplo de Evolución Temporal**

| Tiempo (ms) | g_app_tick_cnt | g_task_test_tick_cnt | g_app_runtime_us | WCET | Acción |
|-------------|----------------|---------------------|------------------|------|---------|
| 0 | 0 | 0 | 0 | 0 | Inicialización |
| 1 | 1 | 1 | 0 | 0 | SysTick incrementa |
| 1 | 0 | 0 | ~150 | ~150 | app_update() procesa 1 tick |
| 2 | 1 | 1 | 0 | ~150 | SysTick incrementa |
| 1000 | 1 | 1000 | 0 | ~150 | Acumulación de ticks |
| 1000 | 0 | 0 | ~150 | ~150 | Procesamiento normal |
| 1001 | 1 | 1 | 0 | ~150 | Continúa ciclo |

### **Características del Sistema**

1. **Temporización Basada en Ticks**: 1 ms de resolución
2. **Arquitectura No Bloqueante**: Las tareas consumen ticks acumulados
3. **Protección de Recursos Compartidos**: Uso de `CPSID i`/`CPSIE i` para secciones críticas
4. **Métricas de Rendimiento**: WCET y tiempo total de ejecución
5. **Display LCD**: Muestra "TdSE Bienvenidos" y contador de tests

### **Display LCD - Hello World Embebido**

El sistema muestra en el display:
```
Línea 1: "TdSE Bienvenidos"
Línea 2: "Test Nro: X"   (donde X se incrementa cada ~1000ms)
```

Este sistema representa un **ejemplo completo de sistema embebido en tiempo real** con gestión de tareas, medición de performance y interfaz de usuario mediante display LCD.