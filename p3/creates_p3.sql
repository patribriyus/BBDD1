create table Aeropuerto (
    iata VARCHAR(4) PRIMARY KEY ,
    Nombre VARCHAR(30),
    Ciudad varchar(20),
    Estado VARCHAR(2),
    Pais VARCHAR(20),
	lat  decimal(11,8),
	longit decimal(11,8)
)


create table Compañia (
  Codigo VARCHAR(7) PRIMARY KEY,
  Nombre VARCHAR(40)
)


create table Avion (
  Numero VARCHAR(7) PRIMARY KEY,
  Manufactura VARCHAR(30),
  Modelo VARCHAR(20),
  Tipo_avion VARCHAR(25),
  Tipo_motor VARCHAR(15),
  Anyo INTEGER
)

create table Vuelo(
  origen REFERENCES Aeropuerto(iata),
  destino references Aeropuerto(iata),
  Companya references Compañia(Codigo),
  Avion references AVION(Numero),
  Fecha date,
  Num_vuelo integer,
  Hora_esp_salida INTEGER,
  Hora_def_salida INTEGER,
  Hora_esp_aterrizaje INTEGER,
  Hora_def_aterrizaje INTEGER,
  constraint VUELO_PK primary key(Fecha,Companya,Num_vuelo)
)

create table Cancelacion (
  Companya varchar(7),
  Fecha date,
  Num_Vuelo integer,
  Razon VARCHAR(10),
  CONSTRAINT CANCELACION_PK PRIMARY KEY(Companya,Fecha,Num_Vuelo),
  CONSTRAINT CANCELACION_FK FOREIGN KEY (Fecha,Companya,Num_Vuelo) references VUELO(Fecha,Companya,Num_vuelo)
)

create table Retraso(
  Compañia varchar(7),
  Fecha date,
  Num_Vuelo integer,
  Tipo_retraso VARCHAR(20),
  Tiempo_retraso INTEGER,
  CONSTRAINT retraso_PK primary key (Compañia,Fecha,Num_Vuelo,Tipo_retraso),
  constraint retraso_FK foreign key (Compañia,Fecha,Num_Vuelo) references VUELO(Companya,Fecha,Num_vuelo)
)

  create table Desvio(
    Companya_vuelo varchar(7),
    Fecha date,
    Num_Vuelo integer,
    Aeropuerto REFERENCES AEROPUERTO(iata),
    Avion REFERENCES AVION(Numero),
    hora_aterriz INTEGER,
    hora_despegue integer,
    CONSTRAINT DESVIO_PK PRIMARY KEY (Companya_vuelo,Fecha,Num_Vuelo,Aeropuerto),
    CONSTRAINT DESVIO_FK FOREIGN KEY (Companya_vuelo,Fecha,Num_Vuelo) references VUELO(Companya,Fecha,Num_vuelo)
  )