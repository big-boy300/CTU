package shop;

import java.util.ArrayList;


/**
 * Class for shopping cart.
 */

public class ShoppingCart {


    ArrayList<Item1> items;

    public ShoppingCart(ArrayList<Item1> items) {
        this.items = items;
    }

    public ShoppingCart() {
        items = new ArrayList<Item1>();
    }

    /**
     * Gets items in the shopping cart.
     *
     * @return items in the shopping cart
     */
    public ArrayList<Item1> getCartItems() {
        return items;
    }

    public void addItem(Item1 temp_item) {
        items.add(temp_item);
        System.out.println("Item with ID " + temp_item.getID() + " added to the shopping cart.");
    }


    /**
     * Removes item from the shopping chart
     *
     * @param itemID ID of the item to remove form the shopping chart
     */

    public void removeItem(int itemID) {
        for (int i = 0; i < items.size(); ++i) {
            Item1 tmp_item = (Item1) items.get(i);
            if (tmp_item.getID() == itemID) {
                items.remove(i);
                System.out.println("Item with ID " + tmp_item.getID() + " removed from the shopping cart.");
            }
        }
    }

    public int getItemsCount() {
        if (items.size() == 0) {
            return 0;
        }
        return items.size();
    }


    /**
     * Gets total price with discount, if there are any discounted items in the chart
     *
     * @return total price with discount
     */
    public float getTotalPrice() {
        float total = 0;
        for (int i = 0; i < items.size(); ++i) {
            Item1 item_tmp = (Item1) items.get(i);
            total += item_tmp.getPrice();
        }
        return total;
    }

}
