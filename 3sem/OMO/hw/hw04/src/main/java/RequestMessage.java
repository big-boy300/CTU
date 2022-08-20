public class RequestMessage extends Message {
    private final int blockIndex;

    public RequestMessage(int blockIndex, PeerInterface sender) {
        super(sender);
        this.blockIndex = blockIndex;
    }

    public int getBlockIndex() {
        return blockIndex;
    }

    public boolean accept(MessageVisitor visitor) {
        return visitor.visitRequestMessage(this);
    }
}
