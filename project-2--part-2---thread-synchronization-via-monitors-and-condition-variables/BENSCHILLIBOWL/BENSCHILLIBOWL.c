#include "BENSCHILLIBOWL.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#define ARR_SIZE(BENSCHILLIBOWLMenu) ( sizeof((BENSCHILLIBOWLMenu)) / sizeof((BENSCHILLIBOWLMenu[0])) )

bool IsEmpty(BENSCHILLIBOWL* mcg);
bool IsFull(BENSCHILLIBOWL* mcg);
void AddOrderToBack(Order **orders, Order *order);

MenuItem BENSCHILLIBOWLMenu[] = { 
    "BensChilli", 
    "BensHalfSmoke", 
    "BensHotDog", 
    "BensChilliCheeseFries", 
    "BensShake",
    "BensHotCakes",
    "BensCake",
    "BensHamburger",
    "BensVeggieBurger",
    "BensOnionRings"
};
int BENSCHILLIBOWLMenuLength = 10;

/* Select a random item from the Menu and return it */
MenuItem PickRandomMenuItem() { 
  return BENSCHILLIBOWLMenu[rand() % ARR_SIZE(BENSCHILLIBOWLMenu)];
}

/* Allocate memory for the Restaurant, then create the mutex and condition variables needed to instantiate the Restaurant */

BENSCHILLIBOWL* OpenRestaurant(int max_size, int expected_num_orders) {
    BENSCHILLIBOWL *bcb = malloc(sizeof(BENSCHILLIBOWL));
    pthread_mutex_init(bcb->mutex, NULL);
    pthread_cond_init(bcb->can_add_orders, NULL);
    pthread_cond_init(bcb->can_get_orders, NULL);
    printf("Restaurant is open!\n");
    return NULL;
}


/* check that the number of orders received is equal to the number handled (ie.fullfilled). Remember to deallocate your resources */

void CloseRestaurant(BENSCHILLIBOWL* mcg) {
    Order *tmp;
    
    if (mcg->current_size == mcg->orders_handled) {
        while (mcg->orders) { // deletes orders linked list
            tmp = mcg->orders;
            free(mcg->orders);
            mcg->orders = tmp->next;
        }
        free(mcg);
    }
    printf("Restaurant is closed!\n");
}

/* add an order to the back of queue */
int AddOrder(BENSCHILLIBOWL* mcg, Order* order) {
    order->next = NULL;
    AddOrderToBack(mcg->orders,order);
    return -1;
}

/* remove an order from the queue */
Order *GetOrder(BENSCHILLIBOWL* mcg) {
    Order *o = mcg->orders;
    mcg->orders = o->next;
    return o;
}

// Optional helper functions (you can implement if you think they would be useful)
bool IsEmpty(BENSCHILLIBOWL* mcg) {
  return false;
}

bool IsFull(BENSCHILLIBOWL* mcg) {
  return false;
}

/* this methods adds order to rear of queue */
void AddOrderToBack(Order **orders, Order *order) {
   Order *tmp = orders;
    while (tmp->next) // find last order in list
        tmp = tmp->next;
    tmp->next = order;
}

