package archive;

import shop.Item1;

class ItemPurchaseArchiveEntry {
    private final Item1 refItem;
    private int soldCount;

    ItemPurchaseArchiveEntry(Item1 refItem) {
        this.refItem = refItem;
        soldCount = 1;
    }

    void increaseCountHowManyTimesHasBeenSold(int x) {
        soldCount += x;
    }

    int getCountHowManyTimesHasBeenSold() {
        return soldCount;
    }

    Item1 getRefItem() {
        return refItem;
    }

    @Override
    public String toString() {
        return "ITEM  " + refItem.toString() + "   HAS BEEN SOLD " + getCountHowManyTimesHasBeenSold() + " TIMES";
    }
}
