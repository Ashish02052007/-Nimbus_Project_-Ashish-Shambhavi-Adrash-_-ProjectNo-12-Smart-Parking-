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

