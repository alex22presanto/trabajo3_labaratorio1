#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"

static int ultimoId=0;

Employee* employee_new()
{
    return (Employee*) malloc(sizeof(Employee));
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldo)
{
    Employee* pEmployee=employee_new();
    if(pEmployee!=NULL)
    {
        employee_setId(pEmployee,atoi(idStr));
        employee_setNombre(pEmployee,nombreStr);
        employee_setHorasTrabajadas(pEmployee,atoi(horasTrabajadasStr));
        employee_setSueldo(pEmployee,atoi(sueldo));
    }
    return pEmployee;
}
void employee_delete(Employee* this)
{
    int retorno = -1;
    if(this != NULL)
    {
        free(this);
        retorno = 0;
    }
    return retorno;
}

int employee_setId(Employee* this,int id)
{
    int retorno=-1;
    if (this != NULL && id>0)
    {
        this->id=id;
        retorno=0;
    }
    return retorno;
}

int employee_getId(Employee* this,int* id)
{
    int retorno = -1;
    if(this != NULL && id != NULL)
    {
        *id = this->id;
        retorno = 0;
    }
    return retorno;
}

int employee_idGenerator()
{
    return ultimoId++;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this != NULL && nombre != nombre)
    {
        strncpy(this->nombre,nombre,sizeof(this->nombre));
        retorno = 0;
    }
    return retorno;
}
int employee_getNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this != NULL && nombre != nombre)
    {
        strncpy(nombre,this->nombre,sizeof(nombre));
        retorno = 0;
    }
    return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int retorno=-1;
    if (this != NULL && horasTrabajadas>0)
    {
        this->horasTrabajadas=horasTrabajadas;
        retorno=0;
    }
    return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno = -1;
    if(this != NULL && horasTrabajadas != NULL)
    {
        *horasTrabajadas = this->horasTrabajadas;
        retorno = 0;
    }
    return retorno;
}

int employee_setSueldo(Employee* this,int sueldo)
{
    int retorno=-1;
    if (this != NULL && sueldo>0)
    {
        this->sueldo=sueldo;
        retorno=0;
    }
    return retorno;
}

int employee_getSueldo(Employee* this,int* sueldo)
{
    int retorno = -1;
    if(this != NULL && sueldo != NULL)
    {
        *sueldo = this->sueldo;
        retorno = 0;
    }
    return retorno;
}

int compare_empeladoxnombre(Employee* pEmployee1,Employee* pEmployee2)
{
    char bufferNombre1[128];
    char bufferNombre2[128];
    int retorno = -1;
    if(pEmployee1 != NULL && pEmployee2 != NULL)
    {
        employee_getNombre(pEmployee1,bufferNombre1);
        employee_getNombre(pEmployee2,bufferNombre2);
        retorno=strcmp(bufferNombre1,bufferNombre2);
    }
    return retorno;
}
