
#include "MyLibrary.h"

//-------------------------------- Fonctions d'ajout --------------------------------------//

void addCategory(CATEGORY **categories, int *categoryCount) ;

void addProduct(PRODUCT **products, CATEGORY *category) ;

void addProductToCategory(PRODUCT **products, int *productCount, CATEGORY *categories, int categoryCount);

void addCustomer(CUSTOMER **customers, int *customerCount) ;

void createOrder( CUSTOMER *customer, CATEGORY *categories, ORDER **orders, int *orderCount, int categoryCount, int customerCount)  ;

//--------------------- Foncions pour trouver les indexs --------------------//

int findCustomerIndex(int customerID, CUSTOMER * customers, int customerCount) ;

int findProductIndex(int productID, PRODUCT *products, int numProducts)  ;

int findCategoryIndex(int categoryID, CATEGORY *categories, int categoryCount) ;

int findOrderIndex(int orderID, ORDER * orders,int  orderCount);

//-------------------------------- Fonctions de suppression -------------------------------------//

void removeProductFromCategory(CATEGORY *categories, int categoryCount, int categoryID, int productID);

void removeCustomer(CUSTOMER *customers, int customerCount, int customerID) ;

void removeOrder(ORDER *orders, int orderCount, int orderID);

void removeCustomer(CUSTOMER *customers, int customerCount, int customerID);

void removeCategory(CATEGORY **categories, int *categoryCount, int categoryID);

//-------------------------------------  Fonctions pour l'affichage ----------------------------------------//

float calculateCategoryTotal(CATEGORY *category) ;

void displayProduct(PRODUCT product) ;

void displayCategory(CATEGORY category) ;

void displayCustomer(CUSTOMER customer);

void displayOrder(ORDER order) ;

void displayOrders(ORDER *orders, int orderCount) ;

void displayAllCategories(CATEGORY *categories, int categoryCount) ;

void displayProductDetails(CATEGORY *categories, int categoryCount, int productID);

void displayResult(RESULT result) ;

void displayResults(RESULT *resultArray, int numResults);

//---------------------- Fonctions pour tester l existance des ID --------------------//

int TestIDCat (int ID, CATEGORY **Tab, int *TabSize) ; 

int TestIDPro (int ID, PRODUCT **Tab, int TabSize) ; 

int TestIDCli (int ID, CUSTOMER **Tab, int *TabSize) ; 

//void createresut (RESULT **resultArray ,int numres );

//void remplirres (RESULT **resultArray ,RESULT *res,int numres);

//-------------------------- Result --------------------------------------//
void fillResults(RESULT ***resultArray, ORDER *orders, int orderCount);

int findMostExpensiveOrderIndex(RESULT **resultArray, int orderCount);

void displayMostExpensiveOrder(RESULT **resultArray, int orderCount) ;

//void displayFiles();

//void displayAndModifyStructureAtPosition(int position) ;


//------------------------------------- Fonctions pour les fichier ----------------------------------------//
void createfile(FILE **fp,FILE **fi);
void fillfile(FILE *f,FILE *findex);
void addCustomer(CUSTOMER * c);
CUSTOMER readcustomer (FILE *f);
void displayfile(FILE *f,FILE *fi);

void modifyCustomer(FILE *f, FILE *fi, int position);

//les fonctions et les procedures 
//
//void addCategory(CATEGORY **categories, int *categoryCount) ;
//
//void addProduct(PRODUCT **products, CATEGORY *category) ;
//
////void addProductToCategory(CATEGORY *categories, int categoryCount) ;
//void addProductToCategory(PRODUCT **products, int *productCount, CATEGORY *categories, int categoryCount);
//
//int findProductIndex(int productID, PRODUCT *products, int numProducts)  ;
//
//int findCategoryIndex(int categoryID, CATEGORY *categories, int categoryCount) ;
//
//int findMostExpensiveOrderIndex(RESULT **resultArray, int orderCount);
//
//void addCustomer(CUSTOMER **customers, int *customerCount) ;
//
////void createOrder(CUSTOMER *customer,CATEGORY * category , PRODUCT *products, ORDER **orders, int *orderCount, int productCount,int categoryCount, int customerCount) ;
//void createOrder( CUSTOMER *customer, CATEGORY *categories, ORDER **orders, int *orderCount, int categoryCount, int customerCount)  ;
//
//float calculateCategoryTotal(CATEGORY *category) ;
//
//void displayProduct(PRODUCT product) ;
//
//void displayCategory(CATEGORY category) ;
//
//void displayCustomer(CUSTOMER customer);
//
//void displayOrder(ORDER order) ;
//
//void displayOrders(ORDER *orders, int orderCount) ;
//
//void displayAllCategories(CATEGORY *categories, int categoryCount) ;
//
//void displayResult(RESULT result) ;
//
//void displayResults(RESULT *resultArray, int numResults);
//
//int TestIDCat (int ID, CATEGORY **Tab, int *TabSize) ; 
//
//int TestIDPro (int ID, PRODUCT **Tab, int TabSize) ; 
//
//int TestIDCli (int ID, CUSTOMER **Tab, int *TabSize) ; 
///*
//PRODUCT* findProductByID(PRODUCT *products, int productCount, int productID) ;
//
//CATEGORY* findCategoryByID(CATEGORY *categories, int categoryCount, int categoryID)  ;
//
//CUSTOMER* findCustomerByID(CUSTOMER *customers, int customerCount, int customerID) ;
//
//ORDER* findorderByID(ORDER *order, int orderCount, int orderID) ;*/
//
//void createresut (RESULT **resultArray ,int numres );
//
//void remplirres (RESULT **resultArray ,RESULT *res,int numres);
//
//void fillResults(RESULT ***resultArray, ORDER *orders, int orderCount);
//
////void displayMostExpensiveOrders(RESULT *resultArray, int orderCount);
//void displayMostExpensiveOrder(RESULT **resultArray, int orderCount) ;
//
////void fillFiles(RESULT *resultArray, int orderCount);
//
//void displayFiles();
//
//void displayAndModifyStructureAtPosition(int position) ;
//
////void openfile(FILE **fs , const char *n);
//void fillFiles(RESULT *resultArray, int orderCount, const char * fs_filename ,const char * fi_filename);
//void displayFiles(const char * fs_filename ,const char * fi_filename);
//
////--------------------------- File -----------------------------------
//void creerfichier(FILE **fp,FILE **fi);
//void remplirFichier(FILE *f,FILE *findex);
//void addCustomer(CUSTOMER * c);
//CUSTOMER readcustomer (FILE *f);
//void displayFile(FILE *f,FILE *fi);

