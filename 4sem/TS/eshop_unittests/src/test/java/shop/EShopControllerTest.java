package shop;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import storage.NoItemInStorage;

public class EShopControllerTest {
    private int idStdItem;
    private String nameStdItem;
    private float priceStdItem;
    private String categoryStdItem;
    private int loyaltyPointsStdItem;
    private StandardItem standardItem;

    private String customerName;
    private String customerAddress;

    @BeforeEach
    public void setUp() {
        EShopController.startEShop();
        idStdItem = 300;
        nameStdItem = "1984";
        priceStdItem = 19.84f;
        categoryStdItem = "Literature";
        loyaltyPointsStdItem = 100;
        customerName = "Diogenes";
        customerAddress = "Ancient Greece";
        standardItem = new StandardItem(idStdItem, nameStdItem, priceStdItem,
                categoryStdItem, loyaltyPointsStdItem);
    }

    @Test
    public void eShopController_ProcessTest() {
        ShoppingCart cart = EShopController.newCart();

        //try to purchase empty shopping cart
        Assertions.assertThrows(NoItemInStorage.class,
                () -> {
                    EShopController.purchaseShoppingCart(cart, customerName, customerAddress);
                });

        //try to add item to shopping cart
        cart.addItem(standardItem);
        Assertions.assertEquals(1, cart.getItemsCount());

        //try to remove item from full shopping cart
        cart.removeItem(standardItem.getID());
        Assertions.assertEquals(0, cart.getItemsCount());
        Assertions.assertFalse(cart.getCartItems().contains(standardItem));

        //try to remove item from empty shopping cart
        cart.removeItem(standardItem.getID());
        Assertions.assertFalse(cart.getCartItems().contains(standardItem));

        //try to count overall price
        cart.addItem(standardItem);
        Assertions.assertEquals(priceStdItem, cart.getTotalPrice());

        //try to buy items that are in stock
        int itemCount = 1;
        EShopController.getStorage().insertItems(standardItem, itemCount);
        Assertions.assertDoesNotThrow(
                () -> {
                    EShopController.purchaseShoppingCart(cart, customerName, customerAddress);
                });
        itemCount--;
        Assertions.assertEquals(itemCount, EShopController.getStorage().getItemCount(standardItem.getID()));

        //try to buy items that are out of stock
        cart.removeItem(standardItem.getID());
        EShopController.getStorage().insertItems(standardItem, itemCount);
        Assertions.assertThrows(NoItemInStorage.class,
                () -> {
                    EShopController.purchaseShoppingCart(cart, customerName, customerAddress);
                });

    }
}
