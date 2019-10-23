# Sistema de acceso por RFID con Arduino
El sistema puede dividirse en 3 partes. Por un lado, tenemos el módulo RTC que nos permite conocer la hora y fecha actual. En el módulo 
SD Card podemos leer y escribir datos por medio de un fichero, nosotros lo usaremos como un datalogger para almacenar toda la información. 
Por óltimo, tenemos el módulo RFID RC522, el cual se encarga de leer las tarjetas. Teniendo el contexto de lo que hace cada módulo, 
construiremos un sistema de acceso a usuarios por RFID con datalogger. Su funcionamiento se basa en leer, por medio del módulo RC522, 
las tarjetas RFID, cada tarjeta leída pasara por una función de comparación con un id guardado, si coindicen ambos id's entonces se manda 
un mensaje por medio de una lcd 20x4 en la cual se indica que el acceso ha sido autorizado, de lo contrario, mandara un mensaje de que no 
está autorizado el id de la tarjeta. Cada registro, independientemente de que este autorizado o no, se guardara en un archivo de texto cuyo 
contenido es la hora, fecha, id del tag y su valor de autorización. El archivo, como se mencionó previamente, está en texto (.txt) pero tiene
un formato para poder ser interpretado como CSV por medio de Excel, lo cual facilita su lectura.  El sistema cuenta con leds y un pequeño 
buzzer que indican el estado de la lectura de la tarjeta del RFID.

Podrás encontrar este proyecto con más detalles aquí [Sistema de acceso por RFID con Arduino](https://www.proyecto-teos.com/sistema-de-acceso-por-rfid-con-arduino).


### Empezando
Este proyecto se basa en los sensores que hemos usado anteriormente, si no tienes mucha experiencia en el manejo de dichos sensores puedes consultar nuestros repositorios.

- RTC https://github.com/proyectoTEOS/RTC-con-Arduino
- LCD 20x4 https://github.com/proyectoTEOS/Display-LCD-16x2-con-Arduino
- Buzzer https://github.com/proyectoTEOS/Buzzer-con-Arduino
- micro SD https://github.com/proyectoTEOS/Modulo-Micro_SD-con-Arduino
- RFID https://github.com/proyectoTEOS/Lector-de-tarjeta-RFID_RC522-con-Arduino 


### Requisitos
- Tener el IDE de [Arduino](https://www.arduino.cc/en/Main/Software) (o el de tu preferencia) con la versión más actual.
- Contar con las librerías [SD](https://github.com/arduino-libraries/SD), [RTClib](https://github.com/adafruit/RTClib/), [LiquidCrystal_I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library), [MFRC522](https://github.com/miguelbalboa/rfid), Wire y SPI (se incluye con el IDE).
- Tener el material para hacer el proyecto (claro).


### Materiales
Enlistaremos los materiales que se necesitan para realizar el proyecto, pero puedes conseguir componentes similares.
- 1 Arduino UNO R3
- 2 Leds, uno de color rojo y otro verde (o del color que prefieras)
- 3 Resistencias de 330ohms
- 1 Resistencia de 1K ohm
- 1 Transistor NPN BC548
- 1 Protoboard
- 1 Display LCD de 20x4
- 1 Módulo (adaptador) I2C
- 1 Buzzer de 5v
- 1 Módulo MFRC522
- 1 Módulo RTC DS3231
- 1 Módulo microSD Card


### Código
**[Aqui](https://github.com/proyectoTEOS/Sistema-de-acceso-por-RFID-con-Arduino/blob/master/Sistema-de-acceso-por-RFID-con-Arduino.ino)** podrás obtener el link del código, esta comentado de tal forma que puedas entender cada función.


### Diagrama
El siguiente esquemático muestra cómo se debe conectar todos los componentes con la placa.
![](/resources/sistema-de-acceso-por-rfid-con-arduino-diagrama1.jpg)

Si requieres más información de este y otros proyectos, puedes ir a nuestra [página web](https://www.proyecto-teos.com) y dar clic en la parte de proyectos en donde encontraras los códigos, diagramas, hojas de datos, librerías, recursos y una documentación más extensa.