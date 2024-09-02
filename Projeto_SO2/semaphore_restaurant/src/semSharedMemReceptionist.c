/**
 *  \file semSharedReceptionist.c (implementation file)
 *
 *  \brief Problem name: Restaurant
 *
 *  Synchronization based on semaphores and shared memory.
 *  Implementation with SVIPC.
 *
 *  Definition of the operations carried out by the receptionist:
 *     \li waitForGroup
 *     \li provideTableOrWaitingRoom
 *     \li receivePayment
 *
 *  \author Nuno Lau - December 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "probConst.h"
#include "probDataStruct.h"
#include "logging.h"
#include "sharedDataSync.h"
#include "semaphore.h"
#include "sharedMemory.h"

/** \brief logging file name */
static char nFic[51];

/** \brief shared memory block access identifier */
static int shmid;

/** \brief semaphore set access identifier */
static int semgid;

/** \brief pointer to shared memory region */
static SHARED_DATA *sh;

/* constants for groupRecord */
#define TOARRIVE 0
#define WAIT     1
#define ATTABLE  2
#define DONE     3

/** \brief receptioninst view on each group evolution (useful to decide table binding) */
static int groupRecord[MAXGROUPS];


/** \brief receptionist waits for next request */
static request waitForGroup ();

/** \brief receptionist waits for next request */
static void provideTableOrWaitingRoom (int n);

/** \brief receptionist receives payment */
static void receivePayment (int n);

/** \brief decides which table to occupy for group n or if it must wait. */
static int decideAvailableTable();


/**
 *  \brief Main program.
 *
 *  Its role is to generate the life cycle of one of intervening entities in the problem: the receptionist.
 */
int main (int argc, char *argv[])
{
    int key;                                            /*access key to shared memory and semaphore set */
    char *tinp;                                                       /* numerical parameters test flag */

    /* validation of command line parameters */
    if (argc != 4) { 
        freopen ("error_RT", "a", stderr);
        fprintf (stderr, "Number of parameters is incorrect!\n");
        return EXIT_FAILURE;
    }
    else { 
        freopen (argv[3], "w", stderr);
        setbuf(stderr,NULL);
    }

    strcpy (nFic, argv[1]);
    key = (unsigned int) strtol (argv[2], &tinp, 0);
    if (*tinp != '\0') {   
        fprintf (stderr, "Error on the access key communication!\n");
        return EXIT_FAILURE;
    }

    /* connection to the semaphore set and the shared memory region and mapping the shared region onto the
       process address space */
    if ((semgid = semConnect (key)) == -1) { 
        perror ("error on connecting to the semaphore set");
        return EXIT_FAILURE;
    }
    if ((shmid = shmemConnect (key)) == -1) { 
        perror ("error on connecting to the shared memory region");
        return EXIT_FAILURE;
    }
    if (shmemAttach (shmid, (void **) &sh) == -1) { 
        perror ("error on mapping the shared region on the process address space");
        return EXIT_FAILURE;
    }

    /* initialize random generator */
    srandom ((unsigned int) getpid ());              

    /* initialize internal receptionist memory */
    int g;
    for (g=0; g < sh->fSt.nGroups; g++) {
       groupRecord[g] = TOARRIVE;
    }

    /* simulation of the life cycle of the receptionist */
    int nReq=0;
    request req;
    while( nReq < sh->fSt.nGroups*2 ) {
        req = waitForGroup();
        switch(req.reqType) {
            case TABLEREQ:
                   provideTableOrWaitingRoom(req.reqGroup); //TODO param should be groupid
                   break;
            case BILLREQ:
                   receivePayment(req.reqGroup);
                   break;
        }
        nReq++;
    }

    /* unmapping the shared region off the process address space */
    if (shmemDettach (sh) == -1) {
        perror ("error on unmapping the shared region off the process address space");
        return EXIT_FAILURE;;
    }

    return EXIT_SUCCESS;
}

/**
 *  \brief decides table to occupy for group n or if it must wait.
 *
 *  Checks current state of tables and groups in order to decide table or wait.
 *
 *  \return table id or -1 (in case of wait decision)
 */
static int decideTableOrWait(int n)
{
    int tableId = -1;
     //TODO insert your code here
     if (groupRecord[n] == TOARRIVE) {
        // Group has just arrived, check table availability
        tableId = decideAvailableTable();
    }
    return tableId;
}

/**
 *  \brief called when a table gets vacant and there are waiting groups 
 *         to decide which group (if any) should occupy it.
 *
 *  Checks current state of tables and groups in order to decide group.
 *
 *  \return group id or -1 (in case of wait decision)
 */
static int decideNextGroup()
{
     //TODO insert your code here
    for (int i = 0; i < sh->fSt.nGroups; i++) { // Para cada grupo no restaurante
        if (groupRecord[i] == WAIT) {
            // Group is waiting, check table availability
            int tableId = decideAvailableTable();
            if (tableId != -1) {
                // Mesa disponível, atribui mesa ao grupo
                groupRecord[i] = ATTABLE; // Grupo está na mesa
                sh->fSt.assignedTable[tableId] = i; // Atribui mesa ao grupo
                return i;
            }
        }
    }
    return -1;
}

/**
 *  \brief receptionist waits for next request 
 *
 *  Receptionist updates state and waits for request from group, then reads request,
 *  and signals availability for new request.
 *  The internal state should be saved.
 *
 *  \return request submitted by group
 */
static request waitForGroup()
{
    request ret; 

    if (semDown (semgid, sh->mutex) == -1)  {                                                  /* enter critical region */
        perror ("error on the up operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }

    // TODO insert your code here
    sh->fSt.st.receptionistStat = WAIT_FOR_REQUEST; // recepcionista está a espera de um pedido
    
    if (semUp (semgid, sh->mutex) == -1)      {                                             /* exit critical region */
        perror ("error on the down operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }

    // TODO insert your code here
    if (semDown (semgid, sh->fSt.receptionistRequest.reqType) == -1) {  // decrementa o semaforo receptionistRequest atraves do semDown para que o receptionist receba o pedido do grupo
        perror ("error on the up operation for semaphore access (WT)");                         /* exit critical region */
        exit (EXIT_FAILURE);
    }

    if (semDown (semgid, sh->mutex) == -1)  {                                                  /* enter critical region */
        perror ("error on the up operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }

    // TODO insert your code here
    // (valores são guardados em ret)
    ret.reqType = sh->fSt.receptionistRequest.reqType; // tipo de pedido que o grupo fez ao receptionist (TABLEREQ ou BILLREQ)
    ret.reqGroup = sh->fSt.receptionistRequest.reqGroup; // grupo que fez o pedido ao receptionist
    sh->fSt.receptionistRequest.reqType = -1; // reseta o tipo de pedido que o grupo fez ao receptionist
    sh->fSt.receptionistRequest.reqGroup = -1; // reseta o grupo que fez o pedido ao receptionist
    sh->fSt.st.receptionistStat = WAIT_FOR_REQUEST; // recepcionista volta a estar a espera de um pedido
    saveState(nFic, &sh->fSt); // salva estado

    if (semUp (semgid, sh->mutex) == -1) {                                                  /* exit critical region */
     perror ("error on the down operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }

    // TODO insert your code here
    return ret;
}

/**
 *  \brief receptionist decides if group should occupy table or wait
 *
 *  Receptionist updates state and then decides if group occupies table
 *  or waits. Shared (and internal) memory may need to be updated.
 *  If group occupies table, it must be informed that it may proceed. 
 *  The internal state should be saved.
 *
 */
static void provideTableOrWaitingRoom (int n)
{
    if (semDown (semgid, sh->mutex) == -1)  {                                                  /* enter critical region */
        perror ("error on the up operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }
    
    int tableId = decideTableOrWait(n);

    if (tableId == -1) {
        // Group must wait
        groupRecord[n] = WAIT; // Grupo está à espera
        sh->fSt.groupsWaiting++; // Incrementa o numero de grupos à espera
        sh->fSt.st.receptionistStat = WAIT_FOR_REQUEST; // recepcionista volta a estar a espera de um pedido
        saveState(nFic, &sh->fSt); // salva estado
    }
    else {
        // Group may occupy table
        groupRecord[n] = ATTABLE; // Grupo está na mesa
        sh->fSt.assignedTable[tableId] = n; // Atribui mesa ao grupo
        sh->fSt.st.receptionistStat = WAIT_FOR_REQUEST; // recepcionista volta a estar a espera de um pedido
        saveState(nFic, &sh->fSt); // salva estado
    }

    // TODO insert your code here
    if (semUp (semgid, sh->mutex) == -1) {                                               /* exit critical region */
        perror ("error on the down operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }
}

/**
 *  \brief receptionist receives payment 
 *
 *  Receptionist updates its state and receives payment.
 *  If there are waiting groups, receptionist should check if table that just became
 *  vacant should be occupied. Shared (and internal) memory should be updated.
 *  The internal state should be saved.
 *
 */

static void receivePayment (int n)
{
    if (semDown (semgid, sh->mutex) == -1)  {                                                  /* enter critical region */
        perror ("error on the up operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }

    sh->fSt.st.receptionistStat = RECVPAY;
    saveState(nFic, &sh->fSt); // salva estado

    // Verifica se há grupos à espera e mesas disponíveis
    if (sh->fSt.groupsWaiting > 0) {
        int tableId = decideNextGroup(); // Função para decidir qual grupo ocupará a mesa vaga

        if (tableId != -1) {
            // Atualiza o estado do grupo que ocupará a mesa
            int groupId = sh->fSt.assignedTable[tableId]; // Obtém o grupo que ocupará a mesa
            groupRecord[groupId] = ATTABLE; // Grupo está na mesa
            sh->fSt.groupsWaiting--; // Reduz o número de grupos à espera

            // Informa o grupo que pode ocupar a mesa
            sh->fSt.st.receptionistStat = ASSIGNTABLE; // recepcionista está a atribuir mesa
            sh->fSt.assignedTable[groupId] = tableId; // Atribui mesa ao grupo
            saveState(nFic, &sh->fSt); // Salva o estado
        }
    }

    if (semUp (semgid, sh->mutex) == -1)  {                                                  /* exit critical region */
     perror ("error on the down operation for semaphore access (WT)");
        exit (EXIT_FAILURE);
    }

    // TODO insert your code here
}


// Decide qual mesa está disponível para o grupo
static int decideAvailableTable() { 
    int tableId = -1;

    // Verifica se há uma mesa disponível
    for (int i = 0; i < NUMTABLES; i++) {
        if (sh->fSt.assignedTable[i] == -1) { // Se a mesa está disponível
            tableId = i;
            break;
        }
    }
    return tableId;
}