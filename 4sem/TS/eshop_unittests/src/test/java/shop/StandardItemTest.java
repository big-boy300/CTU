package shop;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

public class StandardItemTest {

    private final int expectedId = 7;
    private final String expectedName = "Book";
    private final float expectedPrice = 10.99f;
    private final String expectedCategory = "Literature";
    private final int expectedLoyaltyPoints = 73;

    @Test
    public void constructorTest_validParameters_StandardItemWithParametersCreated() {
        StandardItem standardItem = new StandardItem(expectedId, expectedName, expectedPrice, expectedCategory, expectedLoyaltyPoints);

        Assertions.assertEquals(expectedId, standardItem.getID());
        Assertions.assertEquals(expectedName, standardItem.getName());
        Assertions.assertEquals(expectedPrice, standardItem.getPrice());
        Assertions.assertEquals(expectedCategory, standardItem.getCategory());
        Assertions.assertEquals(expectedLoyaltyPoints, standardItem.getLoyaltyPoints());
    }

    @Test
    public void copy_StandardItemCopied_SuccessfulCopyOfStandardItem() {
        StandardItem standardItem = new StandardItem(expectedId, expectedName, expectedPrice, expectedCategory, expectedLoyaltyPoints);
        StandardItem itemCopy = standardItem.copy();

        Assertions.assertEquals(standardItem, itemCopy);
        Assertions.assertEquals(expectedId, itemCopy.getID());
        Assertions.assertEquals(expectedName, itemCopy.getName());
        Assertions.assertEquals(expectedPrice, itemCopy.getPrice());
        Assertions.assertEquals(expectedCategory, itemCopy.getCategory());
        Assertions.assertEquals(expectedLoyaltyPoints, itemCopy.getLoyaltyPoints());
    }

    @ParameterizedTest(name = "Items with the same attributes should be the same")
    @CsvSource({"333, The Picture of Dorian Grey, 10.3f, Literature, 96",
            "501, Meditations, 20.223f, Literature, 100"})
    public void equals_standardItem1EqualsStandardItem2_True(int id, String name, float price, String category, int loyaltyPoints) {
        StandardItem standardItem = new StandardItem(id, name, price, category, loyaltyPoints);
        StandardItem standardItemCopy = new StandardItem(id, name, price, category, loyaltyPoints);

        Assertions.assertEquals(true, standardItem.equals(standardItemCopy));
    }

    @ParameterizedTest(name = "Items with different attributes should not be the same")
    @CsvSource({"333, The Picture of Dorian Grey, 10.3f, Literature, 96",
            "501, Meditations, 20.223f, Literature, 100"})
    public void equals_standardItem1EqualsStandardItem2_False(int id, String name, float price, String category, int loyaltyPoints) {
        StandardItem standardItem1 = new StandardItem(id, name, price, category, loyaltyPoints);
        StandardItem standardItem2 = new StandardItem(expectedId, expectedName, expectedPrice, expectedCategory, expectedLoyaltyPoints);

        Assertions.assertEquals(false, standardItem1.equals(standardItem2));
    }

}
