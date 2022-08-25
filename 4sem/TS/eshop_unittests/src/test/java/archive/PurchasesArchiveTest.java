package archive;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;
import shop.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;

public class PurchasesArchiveTest {

    private int idStdItem, idDiscountedItem;
    private String nameStdItem, nameDiscountedItem;
    private float priceStdItem, priceDiscountedItem;
    private String categoryStdItem, categoryDiscountedItem;
    private int loyaltyPointsStdItem;
    private StandardItem standardItem;

    private int discount;
    private String discountFrom;
    private String discountTo;
    private DiscountedItem discountedItem;

    private ArrayList<Item1> items;

    @BeforeEach
    public void setUp() {
        idStdItem = 300;
        nameStdItem = "1984";
        priceStdItem = 19.84f;
        categoryStdItem = "Literature";
        loyaltyPointsStdItem = 100;
        standardItem = new StandardItem(idStdItem, nameStdItem, priceStdItem,
                categoryStdItem, loyaltyPointsStdItem);

        idDiscountedItem = 255;
        nameDiscountedItem = "AirPods";
        priceDiscountedItem = 250.0f;
        categoryDiscountedItem = "Music";
        discount = 20;
        discountFrom = "01.03.2022";
        discountTo = "01.04.2022";
        discountedItem = new DiscountedItem(idDiscountedItem, nameDiscountedItem,
                priceDiscountedItem, categoryDiscountedItem, discount, discountFrom, discountTo);

        items = new ArrayList<>();
        items.add(standardItem);
        items.add(discountedItem);
    }

    @Test
    public void constructorTest() {
        ItemPurchaseArchiveEntry itemPurchaseArchiveEntryInput = new ItemPurchaseArchiveEntry(standardItem);

        Assertions.assertEquals(standardItem, itemPurchaseArchiveEntryInput.getRefItem());
        Assertions.assertEquals(1, itemPurchaseArchiveEntryInput.getCountHowManyTimesHasBeenSold());
    }


    @Test
    public void printItemPurchaseStatistics_oneStandardItemOneAndDiscountedItemArchive_printsCorrectPurchaseStatistics() {
        String expectedOutput = "ITEM PURCHASE STATISTICS:" + System.lineSeparator();
        for (Item1 item : items) {
            expectedOutput += "ITEM  " + item.toString() + "   HAS BEEN SOLD " + 1 + " TIMES" + System.lineSeparator();
        }
        HashMap<Integer, ItemPurchaseArchiveEntry> purchaseArchive = new HashMap<>();
        for (int i = 0; i < items.size(); i++) {
            purchaseArchive.put(items.get(i).getID(), new ItemPurchaseArchiveEntry(items.get(i)));
        }
        PurchasesArchive purchasesArchive = new PurchasesArchive(purchaseArchive, null);
        ByteArrayOutputStream actualOutput = new ByteArrayOutputStream();
        System.setOut(new PrintStream(actualOutput));
        purchasesArchive.printItemPurchaseStatistics();
        Assertions.assertEquals(expectedOutput, actualOutput.toString());
    }

    @Test
    public void getHowManyTimesHasBeenItemSold_twoItemHasBeenSoldFifteenTimes_True() {
        int expectedCount = 15;
        ItemPurchaseArchiveEntry mockedItem = Mockito.mock(ItemPurchaseArchiveEntry.class);
        Mockito.when(mockedItem.getCountHowManyTimesHasBeenSold()).thenReturn(expectedCount);

        HashMap<Integer, ItemPurchaseArchiveEntry> purchaseArchive = new HashMap<>();
        for (Item1 item : items) {
            purchaseArchive.put(item.getID(), mockedItem);
        }
        PurchasesArchive purchasesArchive = new PurchasesArchive(purchaseArchive, null);

        ArrayList<Integer> itemSellingStatistics = new ArrayList<>();
        for (Item1 i : items) {
            itemSellingStatistics.add(purchasesArchive.getHowManyTimesHasBeenItemSold(i));
        }

        ArrayList<Integer> expectedOutput = new ArrayList<>();
        for (int i = 0; i < items.size(); ++i) {
            expectedOutput.add(15);
        }

        Assertions.assertEquals(expectedOutput, itemSellingStatistics);
    }

    @Test
    public void putOrderToPurchasesArchive_OneOrderInArchive_True() {
        String customerName = "Bruce Wayne";
        String customerAddress = "Batcave";
        ShoppingCart cart = new ShoppingCart(items);
        Order order = new Order(cart, customerName, customerAddress);
        HashMap<Integer, ItemPurchaseArchiveEntry> purchaseArchive = new HashMap<>();
        PurchasesArchive purchasesArchive = new PurchasesArchive(purchaseArchive, new ArrayList<>());

        for (int i = 0; i < items.size(); i++) {
            purchaseArchive.put(items.get(i).getID(), new ItemPurchaseArchiveEntry(items.get(i)));
        }

        purchasesArchive.putOrderToPurchasesArchive(order);

        Assertions.assertEquals(order, purchasesArchive.getOrderArchive().get(0));
    }

}
