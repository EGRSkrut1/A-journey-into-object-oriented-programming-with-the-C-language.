#include <iostream>

using namespace std;

// Product
class Product {
private:
	char Title[50];
	char Category[50];
	int Code;
	double Price;
	double Weight;
	bool Available;

	static int Product_count;

public:
	// Default constructor
	Product() : Code(0), Price(0.0), Weight(0.0), Available(false) {
		Title[0] = '\0';
		Category[0] = '\0';
	}

	// Constructor with parameters
	Product(const char* title, const char* category, int code, double price, double weight, bool available)
		: Code(code), Price(price), Weight(weight), Available(available)
	{
		String_copy(Title, title);
		String_copy(Category, category);
	}

	// Destructor
	~Product() {
		String_copy(Title, "");
		String_copy(Category, Category);
	}

	// Getters
	const char* Get_title() const { return Title; }
	const char* Get_category() const { return Category; }
	int Get_code() const { return Code; }
	double Get_price() const { return Price; }
	double Get_weight() const { return Weight; }
	bool Is_available() const { return Available; }

	// Setters
	void Set_title(const char* title) {
		String_copy(Title, title);
	}
	void Set_category(const char* category) {
		String_copy(Category, category);
	}
	void Set_code(int code) { Code = code; }
	void Set_price(double price) { Price = price; }
	void Set_weight(double weight) { Weight = weight; }
	void Set_available(bool available) { Available = available; }

	// The price calculation function
	float Calculating_the_price(int Count, int Choice_product, Product* Arr)
	{
		--Choice_product;
		if (Choice_product >= 0 && Choice_product < Product_count) {
			float Sum = Arr[Choice_product].Price * Count;
			return Sum;
		}
		else {
			cout << "Incorrect product number" << endl;
			return 0.0;
		}
	}

	// Helper function to copy strings
	void String_copy(char* Destination, const char* Source) {
		int i = 0;
		while (Source[i] != '\0' && i < 49) {
			Destination[i] = Source[i];
			++i;
		}
		Destination[i] = '\0';
	}

	// overloading the output operator 
	friend ostream& operator<<(ostream& os, const Product& product) {
		os << "Title: " << product.Title
			<< ", Category: " << product.Category
			<< ", Code: " << product.Code
			<< ", Price: " << product.Price
			<< ", Weight: " << product.Weight
			<< ", Available: " << (product.Available ? "Yes" : "No");
		return os;
	}

	// overloading the input operator
	friend istream& operator>>(istream& is, Product& product) {
		cout << "Enter title: ";
		is.ignore();
		is.getline(product.Title, 50);
		cout << "Enter category: ";
		is.getline(product.Category, 50);
		cout << "Enter code: ";
		is >> product.Code;
		cout << "Enter price: ";
		is >> product.Price;
		cout << "Enter weight: ";
		is >> product.Weight;
		cout << "Is it available? (1 for Yes, 0 for No): ";
		is >> product.Available;
		return is;
	}

	// Menu output function
	void Menu(Product*& Arr, int& Array_size, Product& Foo, const int& Initial_array_size)
	{
		while (true) {
			cout << "0 - Exit" << endl
				<< "1 - Calculate price" << endl
				<< "2 - Print all products" << endl
				<< "3 - Add empty product" << endl
				<< "4 - Add fill product" << endl
				<< "5 - Editing any field" << endl
				<< "6 - Sorting an array" << endl
				<< "7 - Remove product" << endl;

			int Choice;
			int Index;
			int Count;
			cout << "Enter ur choise: ";
			cin >> Choice;

			if (Choice < 0 || Choice > 7) {
				cout << endl << "Incorrect input";
			}

			switch (Choice) {
			case 0:
			{
				cout << "Exiting the program";
				delete[] Arr;
				return;
			}
			case 1:
			{
				int Choice_product;
				cout << "Choice product 1-" << Product_count << ": ", cin >> Choice_product;
				cout << "Enter count: ", cin >> Count;
				cout << "Price: " << Foo.Calculating_the_price(Count, Choice_product, Arr) << endl << endl;
				break;
			}
			case 2:
				// Withdrawal of all products
			{
				cout << endl;
				Foo.Print_all(Arr, Product_count);
				cout << endl;
				break;
			}
			case 3:
				// Adding an empty object
			{
				Foo.Adding_class_object(Arr, Array_size);
				cout << "Success" << endl << endl;
				break;
			}
			case 4:
				// Adding an object to fill in
			{
				Foo.Adding_fill_class_object(Arr, Array_size);
				cout << endl;
				break;
			}
			case 5:
				// Changing fields
			{
				cout << "Enter the index of the product to edit (0-" << Product_count - 1 << "): ", cin >> Index, cout << endl;
				Foo.Changing_fields(Arr, Index);
				cout << endl;
				break;
			}
			case 6:
				// Sorting an array
			{
				Foo.Sort_arr(Arr, Product_count);
				cout << "Array sorted by price" << endl << endl;
				break;
			}
			case 7:
				// Removing a product
			{
				cout << "Enter the index of the product to remove (0-" << Product_count - 1 << "): ", cin >> Index;
				Foo.Removing_product(Arr, Index, Array_size);
				cout << endl;
				break;
			}
			}
		}
	}

	// 1 - Function for adding an empty class object
	void Adding_class_object(Product*& Arr, int& Array_size) {
		if (Product_count == Array_size) {
			int New_size = Array_size * 2;
			Product* New_arr = new Product[New_size];

			for (int i = 0; i < Product_count; ++i) {
				New_arr[i] = Arr[i];
			}

			delete[] Arr;
			Arr = New_arr;
			Array_size = New_size;
		}
		Arr[Product_count] = Product();
		++Product_count;
	}

	// 2 - The function of adding a user-filled class object
	void Adding_fill_class_object(Product*& Arr, int& Array_size) {
		if (Product_count == Array_size) {
			int New_size = Array_size * 2;

			Product* New_arr = new Product[New_size];
			for (int i = 0; i < Product_count; ++i) {
				New_arr[i] = Arr[i];
			}

			delete[] Arr;
			Arr = New_arr;
			Array_size = New_size;
		}

		cout << "Enter product details:" << endl;
		cin >> Arr[Product_count];
		++Product_count;
		cout << "Product added successfully" << endl;
	}

	// Function for removing a product from the array
	void Removing_product(Product*& Arr, int Index, int& Array_size) {
		if (Index >= 0 && Index < Product_count) {
			for (int i = Index; i < Product_count - 1; ++i) {
				Arr[i] = Arr[i + 1];
			}

			--Product_count;
			cout << "Product removed successfully" << endl;
		}
		else {
			cout << "Invalid product index" << endl;
		}
	}

	// 3 - A function for changing any field selected by the user
	void Changing_fields(Product* Arr, int Index) {
		if (Index >= 0 && Index < Product_count) {
			cout << "Enter new product details:" << endl;
			cin >> Arr[Index];
			cout << "Product details changed successfully" << endl;
		}
		else {
			cout << "Invalid product index" << endl;
		}
	}

	// 4 - Function for output of an array
	void Print_all(Product* Arr, int Size) {
		cout << "List of products:" << endl;
		for (int i = 0; i < Size; ++i) {
			cout << "Product " << i + 1 << ": " << Arr[i] << endl;
		}
	}

	// 5 - A function for sorting an array (Bubble Sort)
	void Sort_arr(Product* Arr, int Size) {
		for (int i = 0; i < Size - 1; ++i) {
			for (int j = 0; j < Size - i - 1; ++j) {
				if (Arr[j].Price > Arr[j + 1].Price) {
					Product Temp = Arr[j];
					Arr[j] = Arr[j + 1];
					Arr[j + 1] = Temp;
				}
			}
		}
	}

	static int Get_Product_count() { return Product_count; }
	static void Set_Product_count(int count) { Product_count = count; }
};

int Product::Product_count = 0;

const int Initial_array_size = 3;

int main() {
	Product* Arr = new Product[Initial_array_size]{
		Product("Banana", "Berry", 107, 199.98, 0.2, true),
		Product("Apple", "Fruit", 101, 100.50, 0.15, true),
		Product("Bread", "Bakery", 201, 50.00, 0.5, true)
	};

	Product::Set_Product_count(Initial_array_size);

	int Array_size = Initial_array_size;
	Product Foo;

	Foo.Menu(Arr, Array_size, Foo, Initial_array_size);
}