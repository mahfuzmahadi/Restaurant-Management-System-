#include<stdio.h>
#include<string.h>

struct Item
{
    char name[40];
    char type[30];
    float price;
};

struct Item items[10] = {
                        {"TEA","main",40.00},
                        {"COFFEE","main",50.00},
                        {"COLD COFFEE","starter",150.00},
                        {"LASSI","main",70.00},
                        {"JUICE","starter",100.00},
                        {"COLD DRINKS","main",100.00}
                    };
int total_item_in_restaurant = 6;

struct Cart
{
    struct Item items[10];
    int quantities[10];
    int total_item;
};

struct Cart past_order_list[100];
int number_of_orders = 0;

struct Cart cart;

void view_items()
{
	int i = 0;
    for (i = 0; i < total_item_in_restaurant; i++)
    {
        system("COLOR 0B");
        printf("\n\tSl No: %d. \tName: %s. \t\tType: %s. \t\tPrice: %.2f\n", i+1, items[i].name, items[i].type, items[i].price);
    }
}
void filter_items(){
    system("COLOR 0A");
    printf("\n\twhat type of item do want?\n");
    printf("\t1. Starter\n");
    printf("\t2. Main dish");
    int choice;
    printf("\n\n\tEnter your choice: ");
    scanf("%d", &choice);
    if (choice == 1){
    	int i = 0;
        for (i = 0; i < total_item_in_restaurant; i++)
        {
            if (strcmp(items[i].type,"starter") == 0)
            {
                printf("\n\tSl No: %d. \tName: %s. \t\tType: %s. \tPrice: %.2f\n", i+1, items[i].name, items[i].type, items[i].price);
            }
        }
    }
    else if(choice == 2)
    {
    	int i = 0;
        for (i = 0; i < total_item_in_restaurant; i++)
        {
            if (strcmp(items[i].type,"main") == 0)
            {
                printf("\n\tSl No: %d. Name: %s. \t\tType: %s. \tPrice: %.2f\n", i+1, items[i].name, items[i].type, items[i].price);
            }
        }
    }
    else{
        printf("invalid input!\n");
    }
}

void add_to_cart()
{
    while (1)
    {
        system("COLOR 0C");
        printf("\n\tEnter 0 to go back to main menu.");
        printf("\n\n\tEnter the serial number of the item you want to add to cart:");
        int n;
        int quantity;
        printf("\n\n\t");
        scanf("%d", &n);

        if (n>total_item_in_restaurant)
        {
            printf("Sorry! No such item found");
            continue;
        }
        if (n == 0)
        {
            break;
        } else
        {
            printf("\tType Quantity: ");
            scanf("%d", &quantity);
            cart.items[cart.total_item] = items[n-1];
            cart.quantities[cart.total_item] = quantity;
            cart.total_item++;
            printf("\n\t%d %s added to the cart\n",quantity,items[n-1].name);
        }
    }
}

void view_cart()
{
    system("COLOR 0D");
    if (cart.total_item == 0)
    {
        printf("\n\tCart is empty.");
    }
	int i = 0;
    for (i = 0; i < cart.total_item; i++)
    {
        printf("\n\tSl No: %d. \tItem: %s. ------------- Quantity: %d.\n",i+1,cart.items[i].name, cart.quantities[i]);
    }
}

void remove_item_from_cart()
{
    system("COLOR 0E");
    if (cart.total_item == 0)
    {
        printf("\n\tCart is empty.");
        return;
    }

    int sl_no;
    printf("\n\tEnter the Sl No of the item of the cart you want to remove: ");
    scanf("%d", &sl_no);

    if (sl_no>cart.total_item)
    {
        printf("\t\tOut of Cart");
        return;
    }

    printf("\n\tItem %d %s removed from the cart\n",sl_no,cart.items[sl_no].name);
    sl_no--;
    int i = sl_no;
    for (i = sl_no; i < cart.total_item-1; i++)
    {
        cart.items[i] = cart.items[i+1];
        cart.quantities[i] = cart.quantities[i+1];
    }
    cart.total_item--;
}

void invoice()
{
    system("COLOR 0A");
    if (cart.total_item == 0)
    {
        printf("\n\tCart is empty.");
    }

    float total_price=0;
    int i = 0;
    for (i = 0; i < cart.total_item; i++)
    {
        printf("\n\tItem: %s ------------- Quantities: %d----- Price for each: %.2f---------Sub Total: %.2f\n",
               cart.items[i].name, cart.quantities[i], cart.items[i].price, cart.items[i].price*cart.quantities[i]);
        total_price += cart.items[i].price*cart.quantities[i];
    }
    printf("\t\t-------------------------------------------------------------------------------------------------\n");
    printf("\t\tGrand Total:                                                                              %.2f\n",total_price);
}

void past_orders()
{
    system("COLOR 0C");
	int i = 0;
    for (i = 0; i < number_of_orders; i++)
    {
        printf("Order %d\n", i);
        struct Cart cart_temp = past_order_list[i];

        if (cart_temp.total_item == 0)
        {
            printf("\n\tYour cart is empty.");
        }

        float total_price=0;
        int i = 0;
        for (i = 0; i < cart_temp.total_item; i++)
        {
            printf("Item: %s ------------- Quantities: %d----- Price of each: %.2f---------Sub Total: %.2f\n",cart_temp.items[i].name, cart_temp.quantities[i], cart_temp.items[i].price, cart_temp.items[i].price*cart_temp.quantities[i]);
            total_price += cart_temp.items[i].price*cart_temp.quantities[i];
        }
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("Grand Total:                                                                              %.2f\n",total_price);
    }
    printf("\n\n");
}

void place_order()
{
    system("COLOR 09");
    printf("\n");
    invoice();
    past_order_list[number_of_orders] = cart;
    cart.total_item = 0;
    number_of_orders++;
    printf("\t\tORDER PLACED!!!");
}


int main()
{
    cart.total_item = 0;
    int choice;
    while (1)
    {

        printf("\n\tChoose one of the following options:\n");
        printf("\t1. View Items.\n");
        printf("\t2. Filter Items.\n");
        printf("\t3. Add to Cart.\n");
        printf("\t4. View Cart.\n");
        printf("\t5. Remove Items from Cart.\n");
        printf("\t6. Invoice.\n");
        printf("\t7. Past Orders.\n");
        printf("\t8. Place Order.\n");
        printf("\t9. Exit\n");
        printf("\n\tENTER YOUR CHOICE: ");
        scanf("%d",&choice);


        if (choice == 1)
        {

            view_items();
        }
        else if(choice == 2)
        {
            filter_items();
        }
        else if(choice == 3)
        {
            add_to_cart();
        }
        else if(choice == 4)
        {
            view_cart();
        }
        else if(choice == 5)
        {
            remove_item_from_cart();
        }
        else if(choice == 6)
        {
            invoice();
        }
        else if(choice == 7)
        {
            past_orders();
        }
        else if(choice == 8)
        {
            place_order();
        }
        else if(choice == 9)
        {
            system("COLOR 30");
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tTHANKS FOR VISITING\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

            break;
        }
        else
        {
            printf("Invalid Input!");
        }

        printf("\n\n\n");
    }
}

