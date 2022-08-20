public abstract class Message {
    private final PeerInterface sender;

    public Message(PeerInterface sender) {
        this.sender = sender;
    }

    public PeerInterface getSender() {
        return sender;
    }

    public abstract boolean accept(MessageVisitor visitor);
}
