#include <stdio.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

int daysInMonth(int month, int year) {
    int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = daysPerMonth[month - 1];

    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            days = 29;
    }
    return days;
}

int validateDate(Date d) {
    if (d.year < 1 || d.month < 1 || d.month > 12 || d.day < 1)
        return 0;
    if (d.day > daysInMonth(d.month, d.year))
        return 0;
    return 1;
}

void setDate(Date *d, int day, int month, int year) {
    d->day = day;
    d->month = month;
    d->year = year;
}

void printDate(Date d) {
    printf("%02d/%02d/%04d\n", d.day, d.month, d.year);
}

void advanceDate(Date *d, int a) {
    while (a > 0) {
        d->day++;

        if (d->day > daysInMonth(d->month, d->year)) {
            d->day = 1;
            d->month++;
            if (d->month > 12) {
                d->month = 1;
                d->year++;
            }
        }
        a--;
    }
}

void reverseDate(Date *d, int a) {
    while (a > 0) {
        d->day--;

        if (d->day < 1) {
            d->month--;
            if (d->month < 1) {
                d->month = 12;
                d->year--;
            }
            d->day = daysInMonth(d->month, d->year);
        }
        a--;
    }
}

int compareDates(Date d1, Date d2) {
    if (d1.year < d2.year) return -1;
    if (d1.year > d2.year) return 1;
    if (d1.month < d2.month) return -1;
    if (d1.month > d2.month) return 1;
    if (d1.day < d2.day) return -1;
    if (d1.day > d2.day) return 1;
    return 0;
}

void dateDiff(Date a, Date b, int *years, int *months, int *days) {
    if (compareDates(a, b) > 0) {
        Date tmp = a; a = b; b = tmp;
    }

    int d1 = a.day, m1 = a.month, y1 = a.year;
    int d2 = b.day, m2 = b.month, y2 = b.year;

    if (d2 < d1) {
        m2 -= 1;
        if (m2 == 0) {
            m2 = 12;
            y2 -= 1;
        }
        d2 += daysInMonth(m2, y2);
    }

    if (m2 < m1) {
        m2 += 12;
        y2 -= 1;
    }

    *years = y2 - y1;
    *months = m2 - m1;
    *days = d2 - d1;
}

int main(void) {
    Date date1, date2;
    int day, month, year;

    printf("Enter the first date (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);
    setDate(&date1, day, month, year);

    if (!validateDate(date1)) {
        printf("Invalid date entered.\n");
        return 1;
    }

    printf("Enter the second date (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);
    setDate(&date2, day, month, year);

    if (!validateDate(date2)) {
        printf("Invalid date entered.\n");
        return 1;
    }

    int years, months, days, choice;

    while (1) {
        printf("\nWhich action would you like to take?\n");
        printf("1. Get the difference\n");
        printf("2. Advance date\n");
        printf("3. Reverse Date\n");
        printf("4. Change the Dates\n");
        printf("4. Exit Program\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            dateDiff(date1, date2, &years, &months, &days);
            printf("Difference: %d years, %d months, %d days\n", years, months, days);
            break;

        case 2: {
            char choice3;
            int number;
            printf("\nAdvance which date?\n");
            printf("a. First Date\n");
            printf("b. Second Date\n");
            printf("Enter your choice: ");
            scanf(" %c", &choice3);

            printf("\nHow many days to advance? \n");
            scanf("%d", &number);

            if (choice3 == 'a') {
                advanceDate(&date1, number);
                printf("\nFirst date after advancing: \n");
                printDate(date1);
            } 
            else if (choice3 == 'b') {
                advanceDate(&date2, number);
                printf("\nSecond date after advancing: \n");
                printDate(date2);
            }
            break;
        }

        case 3: {
            char choice2;
            int number2;
            printf("\nReverse which date?\n");
            printf("a. First Date\n");
            printf("b. Second Date\n");
            printf("Enter your choice: ");
            scanf(" %c", &choice2);

            printf("How many days to reverse? ");
            scanf("%d", &number2);

            if (choice2 == 'a') {
                reverseDate(&date1, number2);
                printf("\nFirst date after reversing: \n");
                printDate(date1);
            } 
            else if (choice2 == 'b') {
                reverseDate(&date2, number2);
                printf("\nSecond date after reversing: \n");
                printDate(date2);
            }
            break;
        }

        case 4:
            printf("\nEnter the new first date (DD MM YYYY): \n");
            scanf("%d %d %d", &day, &month, &year);
            setDate(&date1, day, month, year);

            if (!validateDate(date1)) {
            printf("Invalid date entered.\n");
            return 1;
             }

            printf("Enter the new second date (DD MM YYYY): \n");
            scanf("%d %d %d", &day, &month, &year);
            setDate(&date2, day, month, year);

            if (!validateDate(date2)) {
            printf("Invalid date entered.\n");
            return 1;
            }
            break;
            
        case 5:
            printf("Exiting program...\n");
            return 0;
        }
    }
}
