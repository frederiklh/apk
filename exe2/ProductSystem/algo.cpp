/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

#include <fstream>
#include <iostream>
#include <iterator>

#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <string>


#define PRODUCT_DB_FILE		"product.db"

class Product
{
public:
  Product(const std::string& name, float price, unsigned int sold = 0)
    : name_(name), price_(price), sold_(sold)
  {}
  Product()
    : name_(""), price_(0), sold_(0)
  {}
  
  const std::string& name() const
  {
    return name_;
  }
  
  float price() const
  {
    return price_;
  }

  void setPrice(float newPrice)
  {
    price_ = newPrice;
  }
  
  unsigned int sold() const
  {
    return sold_;
  }
  
  friend std::istream& operator>> ( std::istream& i, Product& p );
  friend std::ostream& operator<< ( std::ostream& o, const Product& p );
  
private:
  std::string   name_;
  float         price_;
  int           sold_;
};
typedef std::vector<Product>  ProductList;


std::ostream& operator<< ( std::ostream& o, const Product& p )
{ 
  return o << p.name_ << " " << p.price_ << " " << p.sold_; 
}

std::istream& operator>> ( std::istream& i, Product& p )
{
    return i >> p.name_ >> p.price_ >> p.sold_;
}



/**
 * Read products from file
 */
void productDBRead(ProductList& pl, const std::string& fileName)
{
    ////OLDSTYLE
    //pl.clear();
    //std::ifstream pFile( fileName.c_str() );
    //while( !pFile.eof() )
    //{
    //  Product p;
    //  pFile >> p;
    //  if( pFile ) pl.push_back( p );
    //}
    pl.clear();
    std::ifstream s(fileName.c_str());
    std::istream_iterator<Product> it1(s);  /* Start of file */
    std::istream_iterator<Product> it2;     /* End Of File */
    copy(it1, it2, std::back_inserter(pl)); /* Calling push_back(...) on pl */
}


/**
 * Printout all products
 */
void printAll(const ProductList& pl)
{
    //   std::cout << "##################################################" << std::endl;
    //   std::cout << "Printing out all products..." << std::endl;
    //   std::cout << "----------------------------" << std::endl;
    //   for(ProductList::const_iterator iter = pl.begin(); iter != pl.end(); ++iter)
    //   {
    //     std::cout << *iter << std::endl;
    //   }  
    //   std::cout << "##################################################" << std::endl;
    std::cout << "##################################################" << std::endl;
    std::cout << "Printing out all products..." << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    std::ostream_iterator<Product> it1(std::cout, "\n");
    copy(pl.begin(), pl.end(), it1);
    
    std::cout << "##################################################" << std::endl;
}



/**
   Add item
*/
void addItem(ProductList& pl)
{
    // ref: http://www.cplusplus.com/reference/iterator/istream_iterator/
    Product p;
    std::cout << "Insert a Product: ";

    std::istream_iterator<Product> eos;              // end-of-stream iterator
    std::istream_iterator<Product> iit (std::cin);   // stdin iterator

    if (iit!=eos) p=*iit;
    
    pl.push_back(p);
}


/**
   Write data to db file
*/
void productDBWrite(const ProductList& pl, const std::string& fileName)
{
    std::cout << "##################################################" << std::endl;
    std::cout << "Saving products to DB..." << std::endl;
    std::cout << "----------------------------" << std::endl;
    
    std::ofstream of(fileName.c_str());
    std::ostream_iterator<Product> out_iterator (of,"\n");
    std::copy( pl.begin(), pl.end(), out_iterator );
    
    std::cout << "##################################################" << std::endl;
}


bool lowerThanTen(Product p){
    if(p.sold() > 9)
        return true;
}
/**
 * Print poorly selling products
 */
void printPoorlySellingProducts(const ProductList& pl)
{
    std::ostream_iterator<Product> output(std::cout, "\n");
    std::remove_copy_if(pl.begin(), pl.end(), output, lowerThanTen);
}


// A Functor 
class discount 
{ 
public:
    // This operator overloading enables calling 
    // operator function () on objects of discount 
    void operator () (Product &p) const { 
        p.setPrice(p.price()*0.90); 
    } 
}; 
/**
 * Set a discount on all products - Using for_each()
 */
void addDiscountUsingForEach(ProductList& pl)
{
    // Using lampda
    //std::for_each(pl.begin(), pl.end(), [](Product &p){ p.setPrice(p.price()*0.90); });
    
    // Using functor
    std::for_each(pl.begin(), pl.end(), discount() );
}


/**
 * Set a discount on all products - Using transform()
 */
void addDiscountUsingTransform(ProductList& pl)
{
    int percentage;
    std::cout << "Enter a percentage(between 10-90): ";

    std::istream_iterator<int> eos;              // end-of-stream iterator
    std::istream_iterator<int> iit (std::cin);   // stdin iterator

    if (iit!=eos) percentage=std::clamp(*iit, 10, 90);
    
    std::transform(pl.begin(), pl.end(), pl.begin(), [](Product &p){ return [](Product &p){ p.setPrice(p.price()*x); } });
}


/**
 * Calculate the total amount of sold products
 */
void calcTotalSoldProducts(ProductList& pl)
{
}


/**
 * Setting discount using bind2nd - OPTIONAL
 */


int main()
{
  bool        running = true;
  ProductList pl;
  
  while(running)
  {
    char choice;
    
    std::cout << "********************" << std::endl;
    std::cout << "Help menu: " << std::endl;
    std::cout << "'1' Read product database" << std::endl;
    std::cout << "'2' Print all items" << std::endl;
    std::cout << "'3' Add item" << std::endl;
    std::cout << "'4' Write product database" << std::endl;
    std::cout << "'5' Print poorly selling products" << std::endl;
    std::cout << "'6' Set a discount on all products (using for_each() )" << std::endl;
    std::cout << "'7' Set a discount on all products (using transform() )" << std::endl;
    std::cout << "'8' Calculate the total amount of sold products" << std::endl;
    
    
    std::cout << "'q' Quit" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> choice;
    
    switch(choice)
    {
      case '1':
        productDBRead(pl, PRODUCT_DB_FILE);
        break;

      case '2':
        printAll(pl);
        break;

      case '3':
        addItem(pl);
        break;

      case '4':
        productDBWrite(pl, PRODUCT_DB_FILE);
        break;

      case '5':
        printPoorlySellingProducts(pl);
        break;
        
      case '6':
        addDiscountUsingForEach(pl);
        break;

      case '7':
        addDiscountUsingTransform(pl);
        break;

      case '8':
        calcTotalSoldProducts(pl);
        break;
        
      case 'q':
      case 'Q':
        running = false;
    }
    
    
  }
}
