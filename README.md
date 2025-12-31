[⬅️ Volver a "Proyectos con Qt"](https://github.com/SantiagoBaeza/proyectos-con-Qt/tree/main)

# Registro y análisis de datos de dron (.DAT)

Este proyecto implementa una aplicación en **Qt** que permite abrir archivos binarios `.DAT` correspondientes al registro de un dron.  
La interfaz gráfica procesa los datos y muestra información relevante en tiempo real mediante gráficos y valores interpolados.

---

## Contexto

Este ejercicio corresponde a una práctica tipo parcial, orientada a reforzar conocimientos sobre:

- Lectura de archivos binarios en C++.
- Manejo de estructuras de datos con `QVector`.
- Visualización de múltiples variables en gráficos con **QCustomPlot**.
- Implementación de algoritmos de integración e interpolación para análisis de datos.

El objetivo principal fue simular un entorno de análisis de vuelo de un dron, integrando tanto la lectura de datos como su representación gráfica y numérica.

---

## Capturas

- **Captura 01**: Interfaz mostrando las gráficas de posición X, posición Y y batería en función del tiempo.  
  ![Interfaz](screenshot.png)

---

## Funcionalidad

- Apertura de archivos binarios `.DAT` mediante un diálogo de selección.  
- Lectura de registros en formato `float` y almacenamiento en vectores (`varx`, `vary`, `time`, `bateria`).  
- Gráficas dinámicas de:
  - Posición X vs tiempo.
  - Posición Y vs tiempo.
  - Nivel de batería vs tiempo.
- Cálculo de energía consumida en un intervalo de tiempo mediante integración numérica.  
- Interpolación de valores (posición y batería) en un instante específico ingresado por el usuario.  
- Visualización de resultados en displays LCD dentro de la interfaz.

---

## Tecnologías utilizadas

- Qt (C++), señales y slots.  
- Librería externa: **QCustomPlot** (DLL).  
- Widgets: QPushButton, QLineEdit, QLabel, QLCDNumber, QCustomPlot.  
- Lectura de archivos binarios con `fopen`, `fread` y manejo de punteros.  
- Algoritmos de integración e interpolación implementados en C++.

---

## Comentarios finales

Los archivos del proyecto están incluidos en este repositorio para que cualquier persona pueda descargarlos y compilarlos localmente en **Qt** con la librería **QCustomPlot**.  
De esta manera, es posible revisar el código, ejecutar la aplicación y comprobar tanto la lectura de archivos binarios como la representación gráfica de los datos del dron.  

Este ejercicio tiene como objetivo servir de práctica avanzada en la **lectura y análisis de datos con Qt**, reforzar el manejo de archivos binarios y dejar registro de mis avances en programación aplicada a sistemas de control y visualización.

---

> 🧩 Estos espacios están en construcción y se actualizan de forma frecuente.
