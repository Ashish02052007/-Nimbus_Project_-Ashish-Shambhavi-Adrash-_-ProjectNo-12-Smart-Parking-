#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_SLOTS 91   // initial count

// car info
struct Car {
    char number[20];
    char size[10];
    int entryHour;
    int exitHour;
};

// slot info
struct Slot {
    int id;
    char size[10];
    int filled;
    struct Car car;
};

struct Slot *slots = NULL;
int totalSlots = START_SLOTS;
float totalMoney = 0;

// initialize the first set of slots
void setupSlots() {
    slots = (struct Slot*) malloc(totalSlots * sizeof(struct Slot));
    if(!slots){
        printf("Memory error.\n");
        return;
    }

    for(int idx = 0; idx < totalSlots; idx++) {
        slots[idx].id = idx + 1;

        if(idx < 30) {
            strcpy(slots[idx].size, "small");
        } else if(idx < 60) {
            strcpy(slots[idx].size, "medium");
        } else {
            strcpy(slots[idx].size, "large");
        }

        slots[idx].filled = 0;    // mark empty
    }
}

// expand when full
void expandSlot() {
    int newCount = totalSlots + 10;    // add 10 more
    struct Slot *t = realloc(slots, newCount * sizeof(struct Slot));
    
    if(!t) {
        printf("Could not expand memory.\n");
        return;
    }

    slots = t;

    for(int j = totalSlots; j < newCount; j++){
        slots[j].id = j + 1;
        strcpy(slots[j].size, "medium");   // medium by default
        slots[j].filled = 0;
    }

    totalSlots = newCount;
    printf("Expanded. Total slots: %d\n", totalSlots);
}

void parkCar() {
    struct Car c;
    printf("Car number: ");
    scanf("%s", c.number);

    printf("Car size (small/medium/large): ");
    scanf("%s", c.size);

    printf("Entry hour: ");
    scanf("%d", &c.entryHour);

    int i;
    for(i = 0; i < totalSlots; i++){
        if(slots[i].filled == 0 && strcmp(slots[i].size, c.size) == 0){
            slots[i].car = c;
            slots[i].filled = 1;
            printf("Parked at slot %d\n", slots[i].id);
            return;
        }
    }

    // no free slot found
    printf("No free slot. Expanding...\n");
    expandSlot();
}

void removeCar() {
    int s;
    printf("Slot to free: ");
    scanf("%d", &s);

    if(s < 1 || s > totalSlots || slots[s-1].filled == 0){
        printf("Invalid slot.\n");
        return;
    }

    printf("Exit hour: ");
    scanf("%d", &slots[s-1].car.exitHour);

    int hrs = slots[s-1].car.exitHour - slots[s-1].car.entryHour;
    if(hrs <= 0) hrs = 1;

    float base = 20, fine = 10;
    float bill = hrs * (base + fine);

    printf("Car %s removed. Hours: %d  Bill: %.2f\n",
           slots[s-1].car.number, hrs, bill);

    totalMoney += bill;
    slots[s-1].filled = 0;
}

void searchCar() {
    char n[20];
    printf("Car number: ");
    scanf("%s", n);

    for(int i = 0; i < totalSlots; i++){
        if(slots[i].filled && strcmp(slots[i].car.number, n) == 0){
            printf("Found at slot %d\n", slots[i].id);
            return;
        }
    }

    printf("Not found.\n");
}

void showSlots() {
    for(int i = 0; i < totalSlots; i++){
        if(slots[i].filled){
            printf("Slot %d [%s] - %s\n", slots[i].id, slots[i].size,
                   slots[i].car.number);
        } else {
            printf("Slot %d [%s] - Empty\n", slots[i].id, slots[i].size);
        }
    }
}

void showReport() {
    int f = 0;
    for(int i = 0; i < totalSlots; i++){
        if(slots[i].filled) f++;
    }

    printf("Slots: %d  Filled: %d  Money: %.2f\n",
           totalSlots, f, totalMoney);
}

int main() {
    int ch;
    setupSlots();

    while(1){
        printf("\n1.Park  2.Remove  3.Search  4.Show  5.Report  6.Exit\nChoice: ");
        scanf("%d", &ch);

        switch(ch){
            case 1: parkCar(); break;
            case 2: removeCar(); break;
            case 3: searchCar(); break;
            case 4: showSlots(); break;
            case 5: showReport(); break;
            case 6:
                free(slots);
                return 0;
            default:
                printf("Invalid.\n");
        }
    }
}
