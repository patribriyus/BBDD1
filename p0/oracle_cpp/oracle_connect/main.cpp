#include "ocilib.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

//propiedades de conexion a la base de datos
string conexion ="vicious.hendrix-oracle.cps.unizar.es";
string usuario ="scott";
string password ="trigger";

OCI_Connection *cn;
OCI_Error *err;

/**
* Metodo para realizar una pregunta SQL a la BD (una sentencia SELECT)
* 
* @param sql
*            sentencia SQL
*/
 
void executeQuery(string sql)
{
    OCI_Statement  *st;
    OCI_Resultset  *rs;
    int i,n;
    
    // Formulamos la pregunta y obtenemos el resultado
    st  = OCI_StatementCreate(cn);
    OCI_ExecuteStmt(st, sql.c_str());
    
    OCI_Error *err = OCI_GetLastError();
    if(OCI_ErrorGetOCICode(err)!=0){
        printf(OCI_ErrorGetString(err));printf("\n");
    }else{
        rs = OCI_GetResultset(st);
        
        //creamos la cabecera de la tabla
        n  = OCI_GetColumnCount(rs);
        for(i = 1; i <= n; i++)
        {
            OCI_Column *col = OCI_GetColumn(rs, i);
            printf(OCI_ColumnGetName(col));printf("\t | ");
        }
         printf("\n------------------------------------------------------------\n");
        
        // Creamos las filas de la tabla con la informacion de la tuplas obtenidas
        while (OCI_FetchNext(rs)){
            for(i = 1; i <= n; i++)
            {
                printf(OCI_GetString(rs, i));printf("\t | ");
            }
            printf("\n");
        }    
        printf("------------------------------------------------------------\n");
    }
}

/**
* Metodo para ejecutar una sentencia SQL que no sea una pregunta, es decir,
* que no devuelva una tabla como resultado.
*
* @param sql
*            sentencia SQL
*/
void executeSentence(string sql)
{
    OCI_Statement  *st;
    // Formulamos la sentencia, no hay resultado
    st  = OCI_StatementCreate(cn);
    OCI_ExecuteStmt(st, sql.c_str());
    OCI_Error *err = OCI_GetLastError();
    if(OCI_ErrorGetOCICode(err)!=0){
        printf(OCI_ErrorGetString(err));printf("\n");
    }else{
        OCI_Commit(cn);
    }
}

/**
* Metodo principal, para ejecutar y probar las conexiones a una base de datos
*/
int main(void)
{
    int opcion;
    //cargamos las librerias
    if (!OCI_Initialize(NULL, NULL, OCI_ENV_CONTEXT)){
        printf("Librerías mal configuradas");
        return EXIT_FAILURE;
    }

    //nos conectamos a la base de datos
    cn = OCI_ConnectionCreate(conexion.c_str(), usuario.c_str(), password.c_str(), OCI_SESSION_DEFAULT);
    if( cn == NULL ){
        printf("No se puede conectar a la base de datos");
        return EXIT_FAILURE;
    }
    
    //menu con opciones disponibles
    printf("Conectado con exito a la base de datos:\n");
    printf("==> Uso\n");
    printf("1. Ejecutar una consulta\n");
    printf("2. Ejecutar una modificacion\n");
    printf("3. Salir\n");
    printf("==> Elige una opcion [1..3]: ");
    cin >> opcion;
    while (opcion != 3) {
        string line;
        getline (cin,line);
        switch (opcion) {
            case 1:
                printf("==> Introduce una sentencia select:\n");
                getline (cin,line);
                executeQuery(line);
                break;
            case 2:
                printf("==> Introduce una sentencia insert/update/delete:\n");
                getline (cin,line);
                executeSentence(line);
                break;
        }
        printf("==> Elige una opcion [1..3]:\n");
        cin >> opcion;
    }
    OCI_Cleanup();
    return EXIT_SUCCESS;
}
