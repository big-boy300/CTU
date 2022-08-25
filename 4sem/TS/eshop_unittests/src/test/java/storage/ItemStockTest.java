package storage;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import shop.Item1;
import shop.StandardItem;

public class ItemStockTest {
    private Item1 item;
    private ItemStock itemStock;

    @BeforeEach
    public void setUp() {
        int id = 300;
        String name = "Marcus Aurelius";
        float price = 13.99f;
        String category = "Philosophy";
        int loyaltyPoints = 100;
        this.item = new StandardItem(id, name, price, category, loyaltyPoints);
        itemStock = new ItemStock(item);
    }

    @Test
    public void constructorTest_ValidItem_ItemStockCreated() {
        int expectedCount = 0;

        Assertions.assertEquals(item, itemStock.getItem());
        Assertions.assertEquals(expectedCount, itemStock.getCount());
    }

    @ParameterizedTest
    @CsvSource({"10, 10", "300, 300"})
    public void increaseItemCount_IncreasingCount_CountIncreased(int increaseValue, int expectedResult) {
        itemStock.IncreaseItemCount(increaseValue);

        Assertions.assertEquals(expectedResult, itemStock.getCount());
    }

    @ParameterizedTest
    @CsvSource({"10, -10", "300, -300"})
    public void decreaseItemCount_DecreasingCount_CountDecreased(int decreaseValue, int expectedResult) {
        itemStock.decreaseItemCount(decreaseValue);

        Assertions.assertEquals(expectedResult, itemStock.getCount());
    }

}
