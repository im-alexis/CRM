// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Alexis Torres
// at39625
// Slip days used: 0
// Spring 2022

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

String wordInv; // holds the name of the item
String nameCus; // holds the name of the customers
int itemCount;// holds the number if items being purchased

int diaperInv = 0;
int bottleInv = 0;
int rattleInv = 0;

int newCustomerFlag = 0;

int highPurchDiaName;//Holds the index tot the customer that purchesed the highest of each item
int highPurchBotName;
int highPurchRatName;

int highPurchDiaAmount = 0; //holds the highest amount purchased in terms of diaper ,bottles ,rattles and by who.
int highPurchBotAmount = 0;
int highPurchRatAmount = 0;



/* clear the inventory and reset the customer database to empty */
void reset() {

    diaperInv = 0;//reset all the counters to zero
    bottleInv = 0;
    rattleInv = 0;

    newCustomerFlag = 0;
    highPurchRatAmount = 0;
    highPurchBotAmount = 0;
    highPurchDiaAmount = 0;

    int i;
    for(i = 0; i<= num_customers; i++){ //clears out all the purchases and names
        customers[i].rattles = 0;
        customers[i].bottles = 0;
        customers[i].diapers = 0;
        StringDestroy(&customers[i].name);
        customers[i].name.ptr = nullptr;
        customers[i].name.len = 0;

    }
    num_customers = 0;
}

void processSummarize() { //For the most part it is the same format only variable vals change

    printf("There are %d Bottles %d Diapers and %d Rattles in inventory\n",bottleInv ,diaperInv, rattleInv);
    printf("We have had a total of %d different customers\n", num_customers);
    if(highPurchBotAmount > 0){
        StringPrint(&customers[highPurchBotName].name);
        printf(" has purchased the most Bottles (%d)\n", highPurchBotAmount);
    }
    if(highPurchBotAmount == 0){ printf("no one has purchased any Bottles\n");}

    if(highPurchDiaAmount > 0){
        StringPrint(&customers[highPurchDiaName].name);
        printf(" has purchased the most Diapers (%d)\n", highPurchDiaAmount);
    }
    if(highPurchDiaAmount == 0){ printf("no one has purchased any Diapers\n");}

    if(highPurchRatAmount > 0){
        StringPrint(&customers[highPurchRatName].name);
        printf(" has purchased the most Rattles (%d)\n", highPurchRatAmount);
    }
    if(highPurchRatAmount == 0){ printf("no one has purchased any Rattles\n");}


}

void processPurchase() {

    readString(&nameCus); // reads the names
    readString(&wordInv); // reads the item
    readNum(&itemCount); // reads the value

    int i;
    for (i = 0; i< num_customers; i++){ // once there is at least one customer in the date base
        if(StringIsEqualTo(&nameCus, &customers[i].name)){ // searches through the array of customer names and finds a match
            newCustomerFlag = 0; // the name was found so its not a new customer
            if (wordInv.ptr[0] == 'B'){ // similar to inventory the first char can match
                if (itemCount > bottleInv ){ // if the items are more than the invertory then print that out and save nothing
                    printf("Sorry ");
                    StringPrint(&nameCus);
                    printf(", we only have %d Bottles\n", bottleInv);
                    break;
                }
                if(bottleInv >= itemCount) {
                    customers[i].bottles = customers[i].bottles + itemCount;
                    bottleInv = bottleInv - itemCount;
                    if(customers[i].bottles  > highPurchBotAmount){
                        highPurchBotAmount =  customers[i].bottles;
                        highPurchBotName = i;
                    }
                }
            }
            if (wordInv.ptr[0] == 'D'){
                if (itemCount > diaperInv ){
                    printf("Sorry ");
                    StringPrint(&nameCus);
                    printf(", we only have %d Diapers\n", diaperInv);
                    break;
                }
                if(diaperInv >= itemCount) {
                    customers[i].diapers = customers[i].diapers + itemCount;
                    diaperInv = diaperInv - itemCount;
                    if(customers[i].diapers > highPurchDiaAmount){
                        highPurchDiaAmount = customers[i].diapers;
                        highPurchDiaName = i;
                    }
                }
            }
            if (wordInv.ptr[0] == 'R'){
                if (itemCount >rattleInv ){
                    printf("Sorry ");
                    StringPrint(&nameCus);
                    printf(", we only have %d Rattles\n", rattleInv);
                    break;
                }
                if(rattleInv >= itemCount){
                    customers[i].rattles = customers[i].rattles + itemCount;
                    rattleInv = rattleInv - itemCount;
                    if(customers[i].rattles  > highPurchRatAmount){
                        highPurchRatAmount = customers[i].rattles ;
                        highPurchRatName = i;
                    }
                }

            }
            break; // leave as soon as you find the name and are finished
        }
        if(i+1 == num_customers){ // if the next i is the num_customers then I know ot has found them since it is still in the for loop
         newCustomerFlag = 1; // set the new customer flag to 1
           break; // break out of the for loop
       }
    }

    if(newCustomerFlag == 1){ // if there is a new
        i++;
        if (wordInv.ptr[0] == 'B'){
            if (itemCount > bottleInv ){
                printf("Sorry ");
                StringPrint(&nameCus);
                printf(", we only have %d Bottles\n", bottleInv);
            }
            if(bottleInv >= itemCount) {
                customers[i].bottles = customers[i].bottles + itemCount;
                bottleInv = bottleInv - itemCount;
                if(customers[i].bottles  > highPurchBotAmount){
                    highPurchBotAmount =  customers[i].bottles;
                    highPurchBotName = i;
                }
                StringReAssign(&customers[i].name, &nameCus);
                num_customers++;

            }
        } //similar to other loops if the first char is B D or R then we know what they are buying
        if (wordInv.ptr[0] == 'D'){
            if (itemCount > diaperInv ){
                printf("Sorry ");
                StringPrint(&nameCus);
                printf(", we only have %d Diapers\n", diaperInv);
            }
            if(diaperInv >= itemCount) {
                customers[i].diapers = customers[i].diapers + itemCount;
                diaperInv = diaperInv - itemCount;
                if(customers[i].diapers > highPurchDiaAmount){
                    highPurchDiaAmount = customers[i].diapers;
                    highPurchDiaName = i;
                }
                StringReAssign(&customers[i].name, &nameCus);
                num_customers++;

            }
        }
        if (wordInv.ptr[0] == 'R'){
            if (itemCount > rattleInv){
                printf("Sorry ");
                StringPrint(&nameCus);
                printf(", we only have %d Rattles\n", rattleInv);
                //StringDestroy(&nameCus);
            }
            if(rattleInv >= itemCount){
                customers[i].rattles = customers[i].rattles + itemCount;
                rattleInv = rattleInv - itemCount;
                if(customers[i].rattles  > highPurchRatAmount){
                    highPurchRatAmount = customers[i].rattles ;
                    highPurchRatName = i;
                }
                StringReAssign(&customers[i].name, &nameCus);
                num_customers++;
            }
        }
        newCustomerFlag = 0;
    }

    if (num_customers == 0){ // runs in this specific if until it gets its first customer, to increment the num_customer to 1
        if (wordInv.ptr[0] == 'B'){
            if (itemCount > bottleInv ){
                printf("Sorry ");
                StringPrint(&nameCus);
                printf(", we only have %d Bottles\n", bottleInv);
            }
            if(bottleInv >= itemCount) {
                StringReAssign(&customers[0].name, &nameCus);
                customers[0].bottles = customers[0].bottles + itemCount;
                bottleInv = bottleInv - itemCount;
                highPurchBotAmount =  customers[0].bottles;
                highPurchBotName = 0;
                num_customers++;
            }
        }
        if (wordInv.ptr[0] == 'D'){
            if (itemCount > diaperInv ){
                printf("Sorry ");
                StringPrint(&nameCus);
                printf(", we only have %d Diapers\n", diaperInv);
            }
            if(diaperInv >= itemCount) {
                StringReAssign(&customers[0].name, &nameCus);
                customers[0].diapers = customers[0].diapers + itemCount;
                diaperInv = diaperInv - itemCount;
                highPurchDiaAmount = customers[0].diapers;
                highPurchDiaName = 0;
                num_customers++;
            }
        }
        if (wordInv.ptr[0] == 'R'){
            if (itemCount >rattleInv ){
                printf("Sorry ");
                StringPrint(&nameCus);
                printf(", we only have %d Rattles\n", rattleInv);
            }
            if(rattleInv >= itemCount){
                StringReAssign(&customers[0].name, &nameCus);
                customers[0].rattles = customers[0].rattles + itemCount;
                rattleInv = rattleInv - itemCount;
                highPurchRatAmount = customers[0].rattles ;
                highPurchRatName = 0;
                num_customers++;
            }
        }
    }
    StringDestroy(&nameCus);
    StringDestroy(&wordInv);
}



void processInventory() {

    readString(&wordInv);
    readNum(&itemCount);

    if (wordInv.ptr[0] == 'B'){ //since there is only three items
        bottleInv = bottleInv + itemCount;//and they all start with a different letter then you can
    }                          // compare only the first letter
    if (wordInv.ptr[0] == 'D'){
        diaperInv = diaperInv + itemCount;
    }
    if (wordInv.ptr[0] == 'R'){
        rattleInv = rattleInv + itemCount;
    }
    StringDestroy(&wordInv);
}
