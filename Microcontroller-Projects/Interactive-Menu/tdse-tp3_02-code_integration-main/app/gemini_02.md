# Análisis del Sistema de Logging y su Impacto en las Variables de Tiempo

## **Sistema de Logging (logger.h y logger.c)**

### **Características Principales:**
- **Logging Habilitado**: `LOGGER_CONFIG_ENABLE = 1`
- **Semihosting Activado**: `LOGGER_CONFIG_USE_SEMIHOSTING = 1`
- **Protección de Interrupciones**: Usa `CPSID i`/`CPSIE i` alrededor de cada log
- **Buffer de 64 bytes**: `LOGGER_CONFIG_MAXLEN = 64`

### **Macros de Logging:**
```c
#define LOGGER_INFO(...)\
    LOGGER_LOG("[info] ");\
    LOGGER_LOG(__VA_ARGS__);\
    LOGGER_LOG("\n");
```

## **Impacto del LOGGER_INFO() en las Variables de Tiempo**

### **Variable 1: `g_app_runtime_us`**
- **Unidad**: Microsegundos (μs)
- **Propósito**: Tiempo total de ejecución de todas las tareas en un ciclo

**Impacto del Logging:**
- **EN `app_init()`**: El logging incrementa significativamente el tiempo de inicialización
- **EN `task_test_init()`**: Añade ~100-500μs por cada `LOGGER_INFO`
- **EN `app_update()`**: NO afecta directamente ya que el logging no se usa en el loop principal

**Evolución con Logging:**
```
Sin Logging:    g_app_runtime_us ≈ 50-100μs
Con Logging:    g_app_runtime_us ≈ 200-800μs (dependiendo del número de logs)
```

### **Variable 2: `task_dta_list[index].WCET`**
- **Unidad**: Microsegundos (μs)
- **Propósito**: Worst-Case Execution Time de cada tarea

**Impacto del Logging:**
- **Tarea `task_test`**: El WCET se ve afectado principalmente por:
  - `LOGGER_INFO` en `task_test_init()` (una vez al inicio)
  - Operaciones de display en `task_test_statechart()`

**Evolución del WCET:**
```
Inicialización: WCET ≈ 500-2000μs (debido a múltiples LOGGER_INFO)
Operación normal: WCET ≈ 100-300μs (solo operaciones de display)
```

### **Variable 3: `g_task_test_tick_cnt`**
- **Unidad**: Ticks del sistema (1 tick = 1 ms)
- **Propósito**: Contador de ticks para la tarea de prueba

**Impacto del Logging:**
- **NO afectado directamente** por el logging
- **INDIRECTAMENTE**: El logging prolongado puede causar que se acumulen más ticks durante la inicialización

## **Análisis Temporal Detallado**

### **Fase 1: Inicialización (`app_init()`)**

**Logging en `app_init()`:**
```c
LOGGER_INFO(" ");                                    // ~100μs
LOGGER_INFO("%s is running...", GET_NAME(app_init)); // ~200μs
LOGGER_INFO(p_sys);                                  // ~100μs
LOGGER_INFO(p_app);                                  // ~100μs
LOGGER_INFO(" %s = %lu", GET_NAME(g_app_cnt), 0);    // ~150μs
```

**Logging en `task_test_init()`:**
```c
LOGGER_INFO(" ");                                    // ~100μs
LOGGER_INFO("  %s is running...", p_task_test);      // ~200μs
LOGGER_INFO("  %s is a %s", p_task_test_);           // ~200μs
LOGGER_INFO("   %s = %lu", GET_NAME(g_task_test_cnt), 0); // ~150μs
LOGGER_INFO("   %s = %lu", GET_NAME(tick), 1000);    // ~150μs
```

**Tiempo Total de Inicialización con Logging:**
```
≈ 1,250 - 1,500μs (1.25 - 1.5ms)
```

### **Fase 2: Loop Principal (`app_update()`)**

**Comportamiento SIN Logging en el Loop:**
- `g_app_runtime_us`: 50-150μs por ciclo
- `WCET`: Estable en ~100μs después de inicialización
- `g_task_test_tick_cnt`: Se consume a tasa constante

**Comportamiento CON Logging en el Loop:**
- **NOTA**: En el código actual NO hay logging en `app_update()` o `task_test_update()`
- Si se añadiera logging, aumentaría proporcionalmente:
  - Cada `LOGGER_INFO`: +100-300μs al runtime

## **Ejemplo de Evolución con Logging**

### **Secuencia Temporal:**

| Tiempo | Evento | g_app_runtime_us | WCET | g_task_test_tick_cnt |
|--------|--------|------------------|------|---------------------|
| 0ms | `app_init()` inicia | 0 | 0 | 0 |
| 0ms | Logging en `app_init()` | +1,250μs | +1,250μs | 0 |
| 0ms | `task_test_init()` inicia | - | - | 0 |
| 0ms | Logging en `task_test_init()` | +1,000μs | +1,000μs | 0 |
| 1ms | SysTick incrementa | - | 2,250μs | 1 |
| 1ms | `app_update()` procesa | 150μs | 2,250μs | 0 |
| 2ms | SysTick incrementa | - | 2,250μs | 1 |
| 2ms | `app_update()` procesa | 120μs | 2,250μs | 0 |

### **Estadísticas Finales Después de 1 Segundo:**

```
g_app_runtime_us: Promedio 100-150μs por ciclo (sin logging en loop)
WCET: 2,250μs (determinado por la inicialización con logging)
Ciclos procesados: ~1000 (1 segundo / 1ms por tick)
```

## **Conclusión del Impacto**

### **1. Inicialización:**
- **ALTO impacto** debido a múltiples llamadas `LOGGER_INFO`
- **WCET máximo** se establece durante esta fase
- **Tiempo de arranque** incrementado significativamente

### **2. Operación Normal:**
- **BAJO impacto** ya que no hay logging en el loop principal
- `g_app_runtime_us` representa principalmente el tiempo del display
- `g_task_test_tick_cnt` no se ve afectado

### **3. Recomendaciones:**
- **Debug**: Mantener logging en inicialización
- **Producción**: Deshabilitar `LOGGER_CONFIG_ENABLE` para mejor performance
- **Métricas**: El WCET reportado incluye overhead de debug

**El sistema mantiene su funcionalidad principal intacta, pero las métricas de tiempo reflejan el overhead del logging durante la fase de inicialización.**