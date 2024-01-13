
struct product {
    int productID;
    char name[100];
    char description[500];
    float price;
    int stockQuantity;
    char brand[50] ;
};
typedef struct product  PRODUCT ;

struct category {
    int categoryID;
    char name[50];
    PRODUCT * products; 
    int numProducts ; // Le nombre de produits dans une categorie
};
typedef struct category CATEGORY ;

struct customer {
    int customerID;
    char name[100];
    char email[100];
    int  nbrOrders ;
};
typedef struct customer CUSTOMER ;

struct order {
    int orderID;
    CUSTOMER * customers; 
   // PRODUCT  * products; 
    CATEGORY * categories; 
    int   nbrProducts;
    int   nbrCategories;
    float totalAmount ;
};
typedef struct order ORDER ;

struct result {
    int orderID;
    float totalAmount ;
};
typedef struct result RESULT ;



