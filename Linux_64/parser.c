#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(char* pFile , LinkedList* pArrayListEmployee)
{

    char bufferId[4096];
    char bufferNombre[4096];
    char bufferHorasTrabajadas[4096];
    char bufferSueldo[4096];
    int retorno = -1;
    Employee *pEmpleado;
    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId ,bufferNombre ,bufferHorasTrabajadas ,bufferSueldo);
        while(!feof(pFile))
        {
            fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",bufferId ,bufferNombre ,bufferHorasTrabajadas ,bufferSueldo);
            pEmpleado = employee_newParametros(bufferId ,bufferNombre ,bufferHorasTrabajadas ,bufferSueldo);
            if(pEmpleado != NULL)
            {
                if(!(ll_add(pArrayListEmployee,pEmpleado)))
                {
                    break;
                }
            }
        }
        if(feof(pFile))
        {
            retorno=0;
        }
    }
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee *pEmpleado;
    if(pFile != NULL && pArrayListEmployee != NULL)
    {
        while(!feof(pFile))
        {
            pEmpleado=employee_new();
            if(pEmpleado != NULL)
            {
                if (fread(pEmpleado,sizeof(Employee),1,pFile)==1);
                {
                    if(!(ll_add(pArrayListEmployee,pEmpleado)))
                    {
                        break;
                    }
                }
                else
                {
                    employee_delete(pEmpleado);
                }
            }
        }
        if(feof(pFile))
        {
            retorno=0;
        }
    }
    return retorno;
}

