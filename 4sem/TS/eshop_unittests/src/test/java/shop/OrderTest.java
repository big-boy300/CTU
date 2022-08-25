package shop;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class OrderTest {

    private final ShoppingCart shoppingCart = new ShoppingCart();
    private final String customerName = "Barry Allen";
    private final String customerAddress = "221B Baker Street";

    @Test
    public void constructorTest_ThreeValidParameters_OrderCreated() {
        Order order = new Order(shoppingCart, customerName, customerAddress);

        Assertions.assertEquals(shoppingCart.getCartItems(), order.getItems());
        Assertions.assertEquals(customerName, order.getCustomerName());
        Assertions.assertEquals(customerAddress, order.getCustomerAddress());
    }

    @Test
    public void constructorTest_FourValidParameters_OrderCreated() {
        int state = 300;
        Order order = new Order(shoppingCart, customerName, customerAddress, state);

        Assertions.assertEquals(shoppingCart.getCartItems(), order.getItems());
        Assertions.assertEquals(customerName, order.getCustomerName());
        Assertions.assertEquals(customerAddress, order.getCustomerAddress());
        Assertions.assertEquals(state, order.getState());
    }

    @Test
    public void constructorTest_ShoppingCartIsNull_NullPointerExceptionThrown() {
        ShoppingCart nullShoppingCart = null;

        Assertions.assertThrows(NullPointerException.class,
                () -> {
                    Order order = new Order(nullShoppingCart, customerName, customerAddress);
                });
    }

}
