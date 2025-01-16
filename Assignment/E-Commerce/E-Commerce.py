def calculate_bill():
    print("="*50)
    print("Welcome to Student's Day Sale!".center(50))
    print("="*50)

    # Dictionary to store item categories and their discounts
    items = {
        1: {"name": "Stationery Items", "discount": 0.10},
        2: {"name": "Bags", "discount": 0.12},
        3: {"name": "Laptops", "discount": 0.15}
    }

    # Display available items
    print("\nAvailable Items and Discounts:")
    for key, value in items.items():
        print(f"{key}. {value['name']} ({value['discount']*100}% off)")

    # Initialize variables
    total_bill = 0
    purchased_items = []

    while True:
        try:
            choice = int(input("\nEnter item category (1-3) or 0 to finish: "))

            if choice == 0:
                break
            if choice not in items:
                print("Invalid choice! Please enter a number between 1 and 3.")
                continue

            quantity = int(input("Enter quantity: "))
            if quantity <= 0:
                print("Quantity must be positive!")
                continue

            price = float(input("Enter item price: $"))
            if price <= 0:
                print("Price must be positive!")
                continue

            # Calculate discounted price
            item = items[choice]
            original_total = price * quantity
            discount_amount = original_total * item["discount"]
            final_price = original_total - discount_amount

            # Store item details
            purchased_items.append({
                "name": item["name"],
                "quantity": quantity,
                "original_price": original_total,
                "discount": discount_amount,
                "final_price": final_price
            })

            total_bill += final_price

            # Show item details
            print(f"\nItem Added:")
            print(f"Item: {item['name']}")
            print(f"Quantity: {quantity}")
            print(f"Original Total: ${original_total:.2f}")
            print(f"Discount Amount: ${discount_amount:.2f}")
            print(f"Final Price: ${final_price:.2f}")

        except ValueError:
            print("Please enter valid numbers!")

    # Display final bill with details
    if total_bill > 0:
        print("\n" + "="*50)
        print("FINAL BILL".center(50))
        print("="*50)
        
        print("\nPurchased Items:")
        print("-"*70)
        print(f"{'Item':<20} {'Qty':<8} {'Original':<12} {'Discount':<12} {'Final'}")
        print("-"*70)
        
        for item in purchased_items:
            print(f"{item['name']:<20} {item['quantity']:<8} ${item['original_price']:<11.2f} ${item['discount']:<11.2f} ${item['final_price']:.2f}")
        
        print("-"*70)
        print(f"\nTotal Amount: ${total_bill:.2f}")
    else:
        print("\nNo items purchased.")

# Run the program
calculate_bill()