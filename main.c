#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define CONSOLE_WIDTH 168
#define MAX_NAME_LENGTH 50
#define MAX_MENU_ITEMS 50
#define MAX_STAFF 10
#define MAX_ABSENT_DAY 25




typedef struct {
char name[MAX_NAME_LENGTH];
int price;
int category; //1 food 2 drinks 3 desserts 4 snacks
char design[100];
int color ;
int quantity;
} menuitem;

typedef struct {
    char name[50];
    int absentdays;
    float salary;
    int password;
} Staff;

typedef struct {
char username[MAX_NAME_LENGTH];
char email[MAX_NAME_LENGTH];
char password[MAX_NAME_LENGTH];
} user;

user usersinfo[200];
int maxusers =0;
int userindex;

menuitem menu[MAX_MENU_ITEMS];
int menucount =0;

menuitem cart[MAX_MENU_ITEMS];
int cartcount = 0;
int total =0;

Staff staff[MAX_STAFF] = {
     {"Abdulrahman", 10, 3000, 1234},
     {"Azzam", 24, 200, 1234}, {"Majed", 5, 4000, 1234}, {"Nour", 0, 5000, 1234}
};
int staffCount = 4;
int totalSales = 0;


void firstscreen();

void pre_screen();

void settings();

void Boss_screen();

void centerprint();

void clearfile(char filename[MAX_NAME_LENGTH]);

void add_to_users (char info[MAX_NAME_LENGTH], char filename[MAX_NAME_LENGTH]);

void menu_edit();

void scan_menu_names();

void scan_menu_category();

void scan_menu_color();

void scan_menu_design();

void scan_menu_price();

void clearscreen(){
system("cls");
system("color F0");
}

void readd_emails(){
    clearfile("emails.txt");
    FILE *pf = fopen("emails.txt","a");
    for(int i=0;i<maxusers;i++)
    {
        fprintf(pf,usersinfo[i].email);
    }
    fclose(pf);
}

void readd_usernames(){
    clearfile("usernames.txt");
    FILE *pf = fopen("usernames.txt","a");
    for(int i=0;i<maxusers;i++)
    {
        fprintf(pf,usersinfo[i].username);
    }
    fclose(pf);
}

void readd_passwords(){
    clearfile("passwords.txt");
    FILE *pf = fopen("passwords.txt","a");
    for(int i=0;i<maxusers;i++)
    {
        fprintf(pf,usersinfo[i].password);
    }
    fclose(pf);
}

void readd_menu_name(){
    clearfile("menu_name.txt");
    FILE *pf = fopen("menu_name.txt","a");
    for(int i=0;i<menucount;i++)
    {
        fprintf(pf,"%s\n",menu[i].name);
    }
    fclose(pf);
}

void readd_menu_price(){
    clearfile("menu_price.txt");
    FILE *pf = fopen("menu_price.txt","a");
    for(int i=0;i<menucount;i++)
    {
        fprintf(pf,"%d\n",menu[i].price);
    }
    fclose(pf);
}

void readd_menu_category(){
    clearfile("menu_category.txt");
    FILE *pf = fopen("menu_category.txt","a");
    for(int i=0;i<menucount;i++)
    {
        fprintf(pf,"%d\n",menu[i].category);
    }
    fclose(pf);
}

void readd_menu_color(){
    clearfile("menu_color.txt");
    FILE *pf = fopen("menu_color.txt","a");
    for(int i=0;i<menucount;i++)
    {
        fprintf(pf,"%d\n",menu[i].color);
    }
    fclose(pf);
}

void readd_menu_design(){
    clearfile("menu_design.txt");
    FILE *pf = fopen("menu_design.txt","a");
    for(int i=0;i<menucount;i++)
    {
        fprintf(pf,"%s\n",menu[i].design);
    }
    fclose(pf);
}

void centerprint(char text[],int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 240+color);
    int length = strlen(text);
    int spaces = (CONSOLE_WIDTH-length)/2;
    printf("%*s%s",spaces,"",text);
}

int wrongans(int *choise) {
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    for (int i = 0; buffer[i]; i++) {
        if (!isdigit(buffer[i])) {
            centerprint("    Invalid input! Please enter numbers only.\n", 4);
            Sleep(700);
            return 1;
        }
    }

    *choise = atoi(buffer);
    return 0;
}

void centerbutton(char text[],int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 240+color);
    int length = strlen(text);
    int spaces = (CONSOLE_WIDTH-length)/2;
    int starlen = length+3;
    printf("%*s+",spaces,"");
    for(int i = 0;i<=starlen;i++){
        printf("=");
    }
    printf("+\n");
    printf("%*s|  %s  |",spaces,"",text);
    printf("\n%*s+",spaces,"");
    for(int i = 0;i<=starlen;i++){
        printf("=");
    }
    printf("+\n\n");
}

void print_orders(){
    char line[MAX_NAME_LENGTH];
    FILE *pf = fopen("orders.txt", "r");
    while(fgets(line,sizeof(line),pf) !=NULL){
            centerprint(line,0);
    }
    fclose(pf);
}

void design(char filename[],int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 240+color);
    FILE *pf = fopen(filename,"r");
    char buffer[255];
    while(fgets(buffer,255,pf) != NULL)
    {
    centerprint(buffer,color);
    }
    printf("\n");
 }

void screens(int choise){
   while(1){
       int numofshowed=0;
     menuitem showedmenu[MAX_MENU_ITEMS];
    for(int i = 0;i<menucount;i++){
        if(menu[i].category == choise){
        showedmenu[numofshowed] = menu[i];
        numofshowed++;
    }}
    clearscreen();
    design("layalina_menu.txt", 0);
    for(int i =0; i<numofshowed;i++){
        char buffer[50];
        sprintf(buffer,"%d. %s            -%d$-",i+1,showedmenu[i].name,showedmenu[i].price);
        centerbutton(buffer,0);
        design(showedmenu[i].design,showedmenu[i].color);
    }
        centerbutton("0.    Back     ",4);
        centerprint("      Select an option : ",0);
        int itemnum,qty;
        if(wrongans(&itemnum) ==1)continue;
        if(itemnum ==0){
                firstscreen();
              }else if(itemnum<0||itemnum>numofshowed){
                    centerprint("    Invalid Choice !\n", 4);
                    Sleep(1000);
                    continue;
              }
        centerprint("      Enter quantity : ",0);
        if(wrongans(&qty) ==1)continue;
        if(qty<=0){
                centerprint("    Invalid Choice !\n", 4);
                Sleep(700);
        }else {
        centerprint("      Item added successfully",2);
        Sleep(700);
        int found = 0;
for (int i = 0; i < cartcount; i++) {
    if (strcmp(cart[i].name, showedmenu[itemnum - 1].name) == 0) {
        cart[i].quantity += qty;
        found = 1;
        break;
    }
}

if (!found) {
    showedmenu[itemnum - 1].quantity = qty;
    cart[cartcount] = showedmenu[itemnum - 1];
    cartcount++;
}


        }
   }
}

void cartscreen(){
    while(1){
            total =0;
    clearscreen();
    design("cart1.txt", 0);

printf("\n\n");
char buffer[100];
if(cartcount == 0){
    centerprint("Your Cart Is Empty",4);
    Sleep(700);
    firstscreen();
}else{
for(int i =0;i<cartcount;i++){
     sprintf(buffer," (%d) %d x %s = %d$\n",i+1,cart[i].quantity,cart[i].name,cart[i].price*cart[i].quantity);
     centerprint(buffer,0);
     total += cart[i].price*cart[i].quantity;
}
char totalmoney[100];
sprintf(totalmoney,"Total : %d$",total);
centerprint(totalmoney,0);
}
printf("\n");

centerbutton("0. Back",4);
centerbutton("99. Remove Item",4);
centerprint("      Select an option : ",0);
int choise;
if(wrongans(&choise) ==1)continue;
   if(choise == 0) {
        firstscreen();
   }else if(choise == 99){
   centerprint("Select Item Number :",4);
   int remove;
   if(wrongans(&remove) ==1)continue;
   if (remove <= 0 || remove > cartcount) {
        centerprint("    Invalid item number!\n", 4);
        Sleep(700);
        continue;
   }
remove--;
total -= cart[remove].price*cart[remove].quantity;
for (int i = remove; i < cartcount - 1; i++) {
        cart[i] = cart[i + 1];
    }
    cartcount--;
    centerprint("    Item removed successfully.\n", 2);
    Sleep(700);
    continue;

    }else {centerprint("    Invalid Choice !\n", 4); Sleep(700);}
    }
}

void calctotalsales(){
    char getsale[MAX_NAME_LENGTH];
    FILE *pf = fopen("totalsales.txt","r");
    while(fgets(getsale,sizeof(getsale),pf) != NULL){
        totalSales += atoi(getsale);
    }
fclose(pf);
}

void clearfile(char filename[MAX_NAME_LENGTH]){
    FILE *pf = fopen(filename,"w");
    fprintf(pf,"");
    fclose(pf);

}

void checkoutscreen(){
        while(1){
                total=0;
            char address[220];
            int ensure;
            int back_now;
            clearscreen();
            design("checkout1.txt", 0);
            char buffer[100];
            if(cartcount == 0){
                centerprint("Nothing ):",4);
                Sleep(700);
                firstscreen();
            }else{
                for(int i =0;i<cartcount;i++){
                    sprintf(buffer," (%d) %d x %s = %d$\n",i+1,cart[i].quantity,cart[i].name,cart[i].price*cart[i].quantity);
                    centerprint(buffer,0);
                    total += cart[i].price*cart[i].quantity;
                }
                char totalmoney[100];
                sprintf(totalmoney,"Total : %d$",total);
                centerprint(totalmoney,0);
                printf("\n");
                centerprint("enter your address: ", 0);
                fgets(address,sizeof(address),stdin);
                address[strcspn(address,"\n")] = 0;
                centerprint("enter 1 to ensure the process:", 0);
                if(wrongans(&ensure) ==1) continue;
                if(ensure==1){
                    char order[500];
                    char emai[MAX_NAME_LENGTH];
                    char tota[MAX_NAME_LENGTH];
                    char totalsales[MAX_NAME_LENGTH];
                add_to_users("================New Order================\n","orders.txt");
                sprintf(emai,"Username : %s\n",usersinfo[userindex].username);
                add_to_users(emai,"orders.txt");
                    for(int i =0;i<cartcount;i++){

                sprintf(order," (%d) %d x %s = %d$\n",
                        i+1,
                        cart[i].quantity,cart[i].name,
                        cart[i].price*cart[i].quantity);
                        add_to_users(order,"orders.txt");
                          }
                sprintf(tota,"Total : %d$\n\n",total);
                add_to_users(tota,"orders.txt");
                sprintf(totalsales,"%d\n",total);
                add_to_users(totalsales,"totalsales.txt");
                centerprint("thank you for your order ", 0);
                printf("\n");
                centerprint("the order will arrives in half an hour",0);
                printf("\n");
                design("thank_you.txt", 4);
                design("heart.txt", 4);

                exit(0);
                }else{
                centerprint("No Problem Take Your Time (:",2);
                Sleep(1000);
                firstscreen();
                }
        }
}
}

void orders_screen(){
    while(1){
    clearscreen();
    int choise;
    char buffer[MAX_NAME_LENGTH];
    print_orders();
    sprintf(buffer,"Total Profit : %d$",totalSales);
    centerbutton(buffer,2);
    centerbutton("99. Clear Orders History",4);
    centerbutton("0. Back",4);
    centerprint("    Select an option : ", 0);
    if(wrongans(&choise) ==1)continue;
    if(choise==0)Boss_screen();
    else if(choise ==99){
        clearfile("totalsales.txt");
        clearfile("orders.txt");
        totalSales =0;
        centerbutton("Done",2);
        Sleep(700);
        continue;
    }
    else centerprint("    Invalid Choice !\n", 4);
}
}

void add_menu(){
while(1){
        char name[MAX_NAME_LENGTH];
        char design[MAX_NAME_LENGTH];
        int category;
        int price;
        int color;
        int choise;
        clearscreen();
        int i;
    centerbutton("Menu",2);
    for(i =0; i<menucount;i++){
        char buffer[50];
        sprintf(buffer,"%d. %s            -%d$-",i+1,menu[i].name,menu[i].price);
        centerbutton(buffer,0);
    }
    centerbutton("1. Add item",2);
    centerbutton("99. Back",4);
    centerprint("Select an option : ",0);
    if(wrongans(&choise) ==1)continue;
    switch(choise){
    case 1 :
        centerprint("Set item name : ",0);
        fgets(name,sizeof(name),stdin);
        if(strcmp(name,"99\n")==0) menu_edit();
        name[strcspn(name,"\n")]=0;
        centerprint("Set item price : ",0);
        if(wrongans(&price) ==1)continue;
        if(price == 99) menu_edit();
        if(price <0) {centerprint("Invalid number !",4); Sleep(700); continue;}
        centerbutton("1.food 2.drinks 3.desserts 4.snacks",0);
        centerprint("Set Item category : ",0);
        if(wrongans(&category) ==1)continue;
        if(category == 99) menu_edit();
        if(category<1||category>4) {centerprint("Invalid number !",4); Sleep(700); continue;}
        centerbutton("0. Black",0);
        centerbutton("1. Blue",1);
        centerbutton("2. Green",2);
        centerbutton("3. Aqua",3);
        centerbutton("4. Red",4);
        centerbutton("5. Purple",5);
        centerbutton("6. Yellow",6);
        centerprint("Set item color : ",0);
        if(wrongans(&color) ==1)continue;
        if(color == 99) menu_edit();
        if(color >6 || color < 0){centerprint("Invalid number !",4); Sleep(700); continue;}
        centerprint("Set item design file : ",0);
        fgets(design,sizeof(design),stdin);
        if(strcmp(name,"99\n")==0) menu_edit();
        centerprint("Adding item to menu...",2);
        printf("\n");
        sprintf(menu[menucount].name,"%s",name);
        sprintf(menu[menucount].design,"%s",design);
        menu[menucount].category = category;
        menu[menucount].color = color;
        menu[menucount].price = price;
        ++menucount;
        Sleep(1500);
        readd_menu_category();
        readd_menu_color();
        readd_menu_design();
        readd_menu_name();
        readd_menu_price();
        centerbutton("Item added successfully",2);
        Sleep(500);
        continue;
    case 99 : menu_edit();
    default : centerprint("    Invalid Choice !\n", 4); Sleep(700);
    }

}
}

void remove_menu(){
while(1){
        int removed;
        int choise;
        centerbutton("Menu",2);
    for(int i =0; i<menucount;i++){
        char buffer[50];
        sprintf(buffer,"%d. %s            -%d$-",i+1,menu[i].name,menu[i].price);
        centerbutton(buffer,0);
    }
    centerbutton("1. Remove item",4);
    centerbutton("0. Back",4);
    centerprint("Select an option : ",0);
    if(wrongans(&choise) ==1)continue;
    if(choise ==0) menu_edit();
    if(choise == 1){
        centerprint("Select item number :",0);
        if(wrongans(&removed) ==1)continue;
        if(removed==0)menu_edit();
        if(removed>menucount || removed <1){centerprint("Invalid number !",4); Sleep(700); continue;}
        else{
                removed--;
            for(int i =removed;i<menucount;i++){menu[i]=menu[i+1];}
            menucount--;
            readd_menu_category();
            readd_menu_color();
            readd_menu_design();
            readd_menu_name();
            readd_menu_price();
            centerbutton("Item removed successfully ",4);
            Sleep(700);
            continue;
        }
    }
    else {centerprint("Invalid number !",4); Sleep(700); continue;}
}
}

void menu_edit(){
while(1){
    int choise;
    clearscreen();
    centerbutton("1. Add items",2);
    centerbutton("2. Remove items",4);
    centerbutton("0. Back",4);
    centerprint("Select an option : ",0);
    if(wrongans(&choise) ==1)continue;
        switch(choise){
            case 1 : add_menu();
            case 2 : remove_menu();
            case 0 : Boss_screen();
            default : centerprint("    Invalid Choice !\n", 4);
        }

}
}

void Boss_screen(){
    while(1){
    int choise;
        char buffer[100];
        clearscreen();
        design("boss.txt", 0);
        sprintf(buffer,"Today's sales: %d$ ", totalSales);
        centerprint(buffer,0);
        printf("\n");
        centerprint("last month sales: 53450$", 0);
        printf("\n");
        centerprint("last month Restaurant expenses and workers' salaries: 36000$", 0);
        printf("\n");
        centerprint("last month profits: 17450$", 0);
        printf("\n");
        centerprint("Staff Summary:", 0);
        printf("\n");
        for (int i = 0; i <staffCount; i++) {
            sprintf(buffer, "%s - working days: %d, Salary: %.2f$, password: %d",
                staff[i].name,
                25 - staff[i].absentdays,
                staff[i].salary,
                staff[i].password);
            centerbutton(buffer, 0);
        }
        centerbutton("1. See past orders",2);
        centerbutton("2. Modify menu items",0);
        centerbutton("0. Back",4);
        centerprint("    Select an option : ", 0);
        if(wrongans(&choise) ==1)continue;
        switch(choise){
            case 2 : menu_edit();
            case 1 : orders_screen();
            case 0 : firstscreen();
            default : centerprint("    Invalid Choice !\n", 4);
        }

    }
}

void staff_screen(){

    while(1){
        int staff_number;
        int staff_password;
        clearscreen();
        design("staff.txt", 0);
        centerbutton("1. Abdulrahman", 0);
        centerbutton("2. Azzam", 0);
        centerbutton("3. Majed", 0);
        centerbutton("4. Nour", 0);
        centerbutton("0. Back",4);
        centerprint("Select an option :",0);
        if(wrongans(&staff_number) ==1) continue;
        if(staff_number==0) firstscreen();
        if(!(staff_number<5 && staff_number>0)) {centerprint("invalid choise",4); Sleep(700); continue;}
        centerprint("Select staff password :",0);
        if(wrongans(&staff_password) ==1) continue;
        if(staff_password == staff[staff_number-1].password){
            clearscreen();
            char buffer[100];
            sprintf(buffer,"welcome %s \n",staff[staff_number-1].name);
            centerprint(buffer,0);
            sprintf(buffer,"last month you absent: %d \n ", staff[staff_number-1].absentdays);
            centerprint(buffer,0);
            sprintf(buffer,"and you salary: %.2f$ \n", staff[staff_number-1].salary);
            centerprint(buffer,0);
            centerprint("to know you salary for this month enter absent days(0-25):\n ", 0);
            int absent_days;
            centerprint("Select an option :",0);
            if(wrongans(&absent_days) ==1) continue;
            if (absent_days >= 0 && absent_days <= MAX_ABSENT_DAY) {
                sprintf(buffer, "your salary for this month:%d$ ", (MAX_ABSENT_DAY - absent_days) * 200);
                centerprint(buffer, 2);
                Sleep(1500);
                firstscreen();
                }
            else {
                centerprint("  Invalid Choice ! Please enter a value between 0 and 25.\n", 4);
                Sleep(700);
            }
            }
        else{

            centerprint("    you are not working here!!!\n", 4);
            Sleep(700);
        }
    }
}

void mode(){
    while(1){
        int mode_choise;
        clearscreen();
        design("mode.txt", 0);
        printf("\n\n");
        centerbutton("1. Boss mode", 4);
        centerbutton("2. staff mode", 0);
        centerbutton("0. Back", 4);
        centerprint("Select mode Number :",0);
        if(wrongans(&mode_choise) ==1) continue;
        if(mode_choise == 1){
            Boss_screen();
        }
        else if(mode_choise == 2){
            staff_screen();
        }
        else if(mode_choise == 0){
            firstscreen();
        }
        else{
            centerprint("    Invalid Choice !\n", 4);
            Sleep(700);
            continue;
        }
    }
}

void change_username(){
    while(1){
            clearscreen();
    char confirmpass[MAX_NAME_LENGTH];
    char newusername[MAX_NAME_LENGTH];
    char buffer[MAX_NAME_LENGTH];
    usersinfo[userindex].username[strcspn(usersinfo[userindex].username,"\n")]=0;
    sprintf(buffer,"Current username : %s",usersinfo[userindex].username);
    centerbutton(buffer,4);
    usersinfo[userindex].username[strcspn(usersinfo[userindex].username,"\0")]='\n';
    centerbutton("00.Back",4);
    centerprint("Enter your new username :",0);
    fgets(newusername,sizeof(newusername),stdin);
    if(strcmp(newusername,"00\n")==0)settings();
    if(strcmp(newusername,usersinfo[userindex].username)==0){
            centerprint("Can't use the same username !",4);
            Sleep(700);
            continue;
    }
    centerprint("Please confirm your password :",0);
    fgets(confirmpass,sizeof(confirmpass),stdin);
    if(strcmp(confirmpass,"00\n")==0)settings();
    if(strcmp(confirmpass,usersinfo[userindex].password)==0){
            sprintf(usersinfo[userindex].username,"%s",newusername);
            readd_usernames();
    centerbutton("Username updated successfully",2);
    Sleep(700);
    firstscreen();
     }else{centerprint("Wrong paswword !",4); Sleep(700); continue;}


    }
}

void change_email(){
    while(1){
    clearscreen();
    char confirmpass[MAX_NAME_LENGTH];
    char newemail[MAX_NAME_LENGTH];
    char buffer[MAX_NAME_LENGTH];
    int isregistered =0;
    usersinfo[userindex].email[strcspn(usersinfo[userindex].email,"\n")]=0;
    sprintf(buffer,"Current username : %s",usersinfo[userindex].email);
    centerbutton(buffer,4);
    usersinfo[userindex].email[strcspn(usersinfo[userindex].email,"\0")]='\n';
    centerbutton("00.Back",4);
    centerprint("Enter your new email :",0);
    fgets(newemail,sizeof(newemail),stdin);
    if(strcmp(newemail,"00\n")==0)settings();
    if(strcmp(newemail,usersinfo[userindex].email)==0){
            centerprint("Can't use the same email !",4);
            Sleep(700);
            continue;
    }
    for(int i=0;i<maxusers;i++){
    if(strcmp(newemail,usersinfo[i].email)==0){
            centerprint("Email is already registered !",4);
    Sleep(700);
    isregistered =1;
    break;
     }
}
   if(isregistered)continue;
    centerprint("Please confirm your password :",0);
    fgets(confirmpass,sizeof(confirmpass),stdin);
    if(strcmp(confirmpass,"00\n")==0)settings();
    if(strcmp(confirmpass,usersinfo[userindex].password)==0){
            sprintf(usersinfo[userindex].email,"%s",newemail);
            readd_emails();
    centerbutton("Email updated successfully",2);
    Sleep(700);
    firstscreen();
     }else{centerprint("Wrong paswword !",4); Sleep(700); continue;}


    }
}

void change_password(){
    while(1){
            clearscreen();
    char confirmpass[MAX_NAME_LENGTH];
    char newpass[MAX_NAME_LENGTH];
    centerbutton("00.Back",4);
    centerprint("Enter your new password :",0);
    fgets(newpass,sizeof(newpass),stdin);
    if(strcmp(newpass,"00\n")==0)settings();
    if(strcmp(newpass,usersinfo[userindex].password)==0){
            centerprint("Can't use the same password !",4);
            Sleep(700);
            continue;
    }
    centerprint("Please confirm your password :",0);
    fgets(confirmpass,sizeof(confirmpass),stdin);
    if(strcmp(confirmpass,"00\n")==0)settings();
    if(strcmp(confirmpass,usersinfo[userindex].password)==0){
            sprintf(usersinfo[userindex].password,"%s",newpass);
            readd_passwords();
    centerbutton("Password updated successfully",2);
    Sleep(700);
    firstscreen();
     }else{centerprint("Wrong paswword !",4); Sleep(700); continue;}


    }
}

void delete_user(){
    clearscreen();
    char reason[MAX_NAME_LENGTH];
    char confirm[MAX_NAME_LENGTH];
    centerbutton("00.Back",2);
    centerprint("Please tell us why you want to delete your account ): ",4);
    fgets(reason,sizeof(reason),stdin);
    if(strcmp(reason,"00\n")==0)settings();
    centerprint("Press 1 to confirm deletation :",4);
    fgets(confirm,sizeof(confirm),stdin);
    if(strcmp(confirm,"00\n")==0)settings();
    if(strcmp(confirm,"1\n")==0){
        for(int i=userindex;i<maxusers;i++){
            usersinfo[i]=usersinfo[i+1];
        }
        readd_emails();
        readd_passwords();
        readd_usernames();
        centerbutton("GOOD BYE",4);
        exit(0);
    }else {centerprint("Enjoy (:",2); Sleep(700); firstscreen();}


}

void settings(){
    while(1){
            clearscreen();
         int choise;
    centerbutton("1. Change your username",0);
    centerbutton("2. change your email",0);
    centerbutton("3. change your password",0);
    centerbutton("99. Delete your account",4);
    centerbutton("0. Back",4);
    centerprint("    Select an option : ", 0);
    if(wrongans(&choise) ==1)continue;
        switch(choise){
            case 1 : change_username();
            case 2 : change_email();
            case 3 : change_password();
            case 99 : delete_user();
            case 0 : firstscreen();
            default : centerprint("    Invalid Choice !\n", 4); Sleep(700);
        }


    }
}

void firstscreen(){
   int choise;

        while (1) {
            clearscreen();
            design("welcome1.txt", 0);
            centerbutton("1. Food", 0);
            design("food.txt",0);
            centerbutton("2. Drinks", 0);
            design("drinks.txt",1);
            centerbutton("3. Desserts", 0);
            design("desserts.txt",5);
            centerbutton("4. Snacks", 0);
            design("snacks.txt",6);
            centerbutton("5. View Cart", 0);
            design("cart.txt",0);
            centerbutton("6. Checkout", 0);
            design("checkout.txt",2);
            centerbutton("7. mode", 0);
            centerbutton("8. Settings",0);
            centerbutton("9. Exit", 4);
            centerprint("    Select an option : ", 0);
            if(wrongans(&choise) ==1)continue;


            switch(choise){
                case 1: screens(choise);
                case 2: screens(choise);
                case 3: screens(choise);
                case 4: screens(choise);
                case 5: cartscreen();
                case 6: checkoutscreen();
                case 7: mode();
                case 8: settings();
                case 9: exit(0);
                default:
                    centerprint("    Invalid Choice !\n", 4);
                    Sleep(700);
                              }
        }
}

void add_to_users (char info[MAX_NAME_LENGTH], char filename[MAX_NAME_LENGTH]){
FILE *pf = fopen(filename,"a");
fprintf(pf,info);
fclose(pf);
}

void login_screen(){
    while(1){
    char email[MAX_NAME_LENGTH];
    char targetemail[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    clearscreen();
    centerbutton("LOGIN",2);
    centerbutton("00. Back",4);
    centerprint("Enter Your Email :",0);
    fgets(email,sizeof(email),stdin);
    if(strcmp(email,"00\n")==0)pre_screen();
    int emailfound =0;
    for(int i=0;i<maxusers;i++){
        if(strcmp(email,usersinfo[i].email)==0){emailfound =1; userindex =i; break;}
    }
    if(!emailfound){centerprint("INVALID EMAIL !!",4); Sleep(700); continue;}
    centerprint("Enter Your Password :",0);
    fgets(password,sizeof(password),stdin);
    if(strcmp(password,"00\n")==0)pre_screen();
    if(strcmp(password,usersinfo[userindex].password)==0){centerprint("DONE",2); Sleep(700); firstscreen();}
    else{centerprint("WRONG PASSWORD !!",4); Sleep(700); continue;}
    }
}

void scan_emails(){
FILE *pf = fopen("emails.txt","r");
int i =0;
while(fgets(usersinfo[i].email,sizeof(usersinfo[i].email),pf) !=NULL){
    i++;
    maxusers++;
}
fclose(pf);
}

void scan_menu_names(){
    menucount = 0;
FILE *pf = fopen("menu_name.txt","r");
int i =0;
char buffer[MAX_NAME_LENGTH];
while(fgets(buffer,sizeof(buffer),pf) !=NULL){
    buffer[strcspn(buffer,"\n")] =0;
    sprintf(menu[i].name,"%s",buffer);
    i++;
    menucount++;
}
fclose(pf);
}

void scan_menu_color(){
    char buffer[MAX_NAME_LENGTH];
FILE *pf = fopen("menu_color.txt","r");
int i =0;
while(fgets(buffer,sizeof(buffer),pf) !=NULL){
        menu[i].color = atoi(buffer);
    i++;
}
fclose(pf);
}

void scan_menu_category(){
    char buffer[MAX_NAME_LENGTH];
FILE *pf = fopen("menu_category.txt","r");
int i =0;
while(fgets(buffer,sizeof(buffer),pf) !=NULL){
        menu[i].category = atoi(buffer);
    i++;
}
fclose(pf);
}

void scan_menu_price(){
    char buffer[MAX_NAME_LENGTH];
FILE *pf = fopen("menu_price.txt","r");
int i =0;
while(fgets(buffer,sizeof(buffer),pf) !=NULL){
        menu[i].price = atoi(buffer);
    i++;
}
fclose(pf);
}

void scan_menu_design(){
FILE *pf = fopen("menu_design.txt","r");
int i =0;
char buffer[MAX_NAME_LENGTH];
while(fgets(buffer,sizeof(buffer),pf) !=NULL){
    buffer[strcspn(buffer,"\n")] =0;
    sprintf(menu[i].design,"%s",buffer);
    i++;
}
fclose(pf);
}

void scan_usernames(){
FILE *pf = fopen("usernames.txt","r");
int i =0;
while(fgets(usersinfo[i].username,sizeof(usersinfo[i].username),pf) !=NULL){
    i++;
}
fclose(pf);
}

void scan_passwords(){
FILE *pf = fopen("passwords.txt","r");
int i =0;
while(fgets(usersinfo[i].password,sizeof(usersinfo[i].password),pf) !=NULL){
    i++;
}
fclose(pf);
}

void register_screen(){
    while(1){
    char username[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];

    clearscreen();
centerbutton("Register Screen",2);
centerbutton("00. Back",4);
centerprint("Enter Your username :",0);
fgets(username,sizeof(username),stdin);
if(strcmp(username,"00\n")==0)pre_screen();
centerprint("Enter Your email :",0);
fgets(email,sizeof(email),stdin);
int isregistered =0;
for(int i=0;i<maxusers;i++){
    if(strcmp(email,usersinfo[i].email)==0){
            centerprint("Email is already registered !",4);
    Sleep(700);
    isregistered =1;
    break;
     }
}
   if(isregistered)continue;
if(strcmp(email,"00\n")==0)pre_screen();
centerprint("Enter Your Password :",0);
fgets(password,sizeof(password),stdin);
if(strcmp(password,"00\n")==0)pre_screen();

add_to_users(email,"emails.txt");
add_to_users(username,"usernames.txt");
add_to_users(password,"passwords.txt");
centerbutton("Register Done",2);
Sleep(1000);

scan_emails();
scan_passwords();
scan_usernames();
login_screen();
}
}

void pre_screen(){
    while(1){
clearscreen();
centerbutton("1. LOGIN",0);
centerbutton("2. REGISTER",0);
centerbutton("0. EXIT",4);
centerprint("Select an option :",0);
int choise;
if(wrongans(&choise) ==1)continue;
switch(choise){
case 1 : login_screen();
case 2 : register_screen();
case 0 : exit(0);
default: {centerprint("INVALID CHOISE !!",4); Sleep(700);}
}
    }
}

void scan_all(){
   scan_emails();
   scan_passwords();
   scan_usernames();
   calctotalsales();
   scan_menu_names();
   scan_menu_category();
   scan_menu_color();
   scan_menu_design();
   scan_menu_price();
}

int main(){
    scan_all();
   pre_screen();
    return 0;
}//control+z
