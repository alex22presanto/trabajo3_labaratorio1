#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "utn.h"


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int i;
    FILE* pFile;
    if(path != NULL && pArrayListEmployee != NULL)
    {
        pFile=fopen(path,"r");
        if (pFile!=NULL)
        {
            retorno=parser_EmployeeFromText(pFile,pArrayListEmployee);
        }
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    FILE* pFile;
    if(path != NULL && pArrayListEmployee != NULL)
    {
        pFile=fopen(path,"rb");
        if (pFile!=NULL)
        {
            retorno=parser_EmployeeFromBinary(pFile,pArrayListEmployee);
        }
    }
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pEmployee=employee_new();
    int bufferId;
    char bufferNombre[128];
    int bufferHorasTrabajadas;
    int bufferSueldo;
    int retorno = -1;

    if( pArrayListEmployee != NULL)
    {
        bufferId=employee_idGenerator();
        utn_getName("Ingrese el nombre:\n","Nombre no valido\n",1,128,3,&bufferNombre);
        utn_getUnsignedInt("Ingrese la cantidad de horas trabajadas:\n","Numero no valido\n",1,sizeof(int),1,1000,3,&bufferHorasTrabajadas);
        utn_getUnsignedInt("Ingrese el suleldo:\n","Numero no valido\n",1,sizeof(int),1,10000,3,&bufferSueldo);
        employee_setId(pEmployee,bufferId);
        employee_setHorasTrabajadas(pEmployee,bufferHorasTrabajadas);
        employee_setNombre(pEmployee,bufferNombre);
        employee_setSueldo(pEmployee,bufferSueldo);
        ll_add(pArrayListEmployee,pEmployee);
        retorno=0;
    }

    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    Employee* bufferEmpleado;
    int bufferId;
    char bufferNombre[128];
    int bufferHorasTrabajadas;
    int bufferSueldo;
    int retorno = -1;
    int index;
    int opcion;

    if(pArrayListEmployee != NULL)
    {
        utn_getUnsignedInt("Ingrese el id:\n","id no valido\n",1,sizeof(int),1,ll_len(pArrayListEmployee),3,&bufferId);
        index=controller_searchEmployeeById(pArrayListEmployee,bufferId);
        if (index > 0)
        {
            bufferEmpleado=ll_get(pArrayListEmployee,index);
            utn_getUnsignedInt("1. Nombre\n2.Horas trabajadas\n3.Sueldo","Opcion no valida",1,sizeof(int),1,3,3,&opcion);
            switch(opcion)
            {
                case 1:
                    utn_getName("Ingrese el nombre:\n","Nombre no valido\n",1,128,3,&bufferNombre);
                    employee_setNombre(bufferEmpleado,bufferNombre);
                    break;
                case 2:
                    utn_getUnsignedInt("Ingrese la cantidad de horas trabajadas:\n","Numero no valido\n",1,sizeof(int),1,1000,3,&bufferHorasTrabajadas);
                    employee_setHorasTrabajadas(bufferEmpleado,bufferHorasTrabajadas);
                    break;
                case 3:
                    utn_getUnsignedInt("Ingrese el sueldo:\n","Numero no valido\n",1,sizeof(int),1,10000,3,&bufferSueldo);
                    employee_setSueldo(bufferEmpleado,bufferSueldo);
                    break;

            }
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    Employee* bufferEmpleado;
    int bufferId;
    int retorno = -1;
    int index;

    if(pArrayListEmployee != NULL)
    {
        utn_getUnsignedInt("Ingrese el id:\n","id no valido\n",1,sizeof(int),1,ll_len(pArrayListEmployee),3,&bufferId);
        index=controller_searchEmployeeById(pArrayListEmployee,bufferId);
        if (index > 0)
        {
            bufferEmpleado=ll_get(pArrayListEmployee,index);
            ll_remove(pArrayListEmployee,index);
            free(bufferEmpleado);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    Employee* bufferEmpleado;
    int bufferId;
    char bufferNombre[128];
    int bufferHorasTrabajadas;
    int bufferSueldo;
    int retorno = -1;
    int size=ll_len(pArrayListEmployee);
    int i;
    if(pArrayListEmployee != NULL)
    {
        for(i=0;i<size;i++)
        {
            bufferEmpleado=ll_get(pArrayListEmployee,i);
            if(bufferEmpleado != NULL)
            {
                employee_getId(bufferEmpleado,&bufferId);
                employee_getHorasTrabajadas(bufferEmpleado,&bufferHorasTrabajadas);
                employee_getNombre(bufferEmpleado,bufferNombre);
                employee_getSueldo(bufferEmpleado,&bufferSueldo);
                printf("%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            }
            retorno=0;
        }
    }
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;

    if (pArrayListEmployee != NULL)
    {
        retorno=ll_sort(pArrayListEmployee,&compare_empeladoxnombre(Employee*,Employee*),1);
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee )
{
    FILE* pFile;
    Employee* pEmployee;

    int bufferID;
    char bufferNombre[4056];
    int bufferHoras;
    int bufferSuledo;
    int size;
    int i,j;
    int retorno=-1;
    if(path != NULL && pArrayListEmployee != NULL)
    {
        pFile= fopen(path,"w+");
        if(pFile!=NULL)
        {
            fprintf(pFile,"id,nombre,horastrabajadas,sueldo");
            size=ll_len(pArrayListEmployee);
            for(i=0;i<size;i++)
            {
                pEmployee=ll_get(pArrayListEmployee,i);
                employee_getId(pEmployee,&bufferID);
                employee_getNombre(pEmployee,bufferNombre);
                employee_getHorasTrabajadas(pEmployee,&bufferHoras);
                employee_getSueldo(pEmployee,&bufferSuledo);
                //employee_getSueldo(pÈmployee,&bufferSuledo);
                j=fprintf(pFile,"%d,%s,%d,%d\n",bufferID,bufferNombre,bufferHoras,bufferSuledo);
            }
            fclose(pFile);
            if(j==0)
                retorno = 0;
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    Employee* pEmployee;

    int size;
    int i;
    int retorno=-1;
    if(path != NULL && pArrayListEmployee != NULL)
    {
        pFile= fopen(path,"w+b");
        if(pFile!=NULL)
        {
            size=ll_len(pArrayListEmployee);
            for(i=0;i<size;i++)
            {
                pEmployee=ll_get(pArrayListEmployee,i);
                fwrite(pEmployee,sizeof(Employee),1,pFile);
            }
            fclose(pFile);
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

int controller_searchEmployeeById(LinkedList* pArrayListEmployee,int valorBuscado)
{
    int retorno = -1;
    int size = ll_len(pArrayListEmployee);
    int i;
    Employee* bufferEmployee;
    int bufferId;

    if(pArrayListEmployee != NULL && valorBuscado > 0)
    {
        for(i=0;i<size;i++)
        {
            bufferEmployee=ll_get(pArrayListEmployee,i);
            if(bufferEmployee !=NULL)
            {
                employee_getId(bufferEmployee,&bufferId);
                if (bufferId == valorBuscado);
                {
                    retorno = i;
                    break;
                }
            }
        }
    }
    return retorno;
}

