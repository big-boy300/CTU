import java.util.*;
import java.util.Map.Entry;

public class Homework4 extends MessageVisitor {
    public Homework4(Peer peer) {
        super(peer);
    }

    @Override
    public boolean visitHaveMessage(HaveMessage message) {
        this.peer.peers2BlocksMap.get(message.getSender())[message.getBlockIndex()] = true;
        return false;
    }

    @Override
    public boolean visitRequestMessage(RequestMessage message) {
        boolean peerHasData = this.peer.data[message.getBlockIndex()] != null;
        if (peerHasData) {
            message.getSender().piece(this.peer, message.getBlockIndex(), this.peer.data[message.getBlockIndex()]);
        }
        return false;
    }

    @Override
    public boolean visitPieceMessage(PieceMessage message) {
        this.peer.data[message.getBlockIndex()] = message.getData();
        this.peer.downloadedBlocksCount++;
        for(var entry : this.peer.peers2BlocksMap.entrySet()){
            entry.getKey().have(this.peer, message.getBlockIndex());
        }
        return peer.downloadedBlocksCount == peer.totalBlocksCount;
    }

    @Override
    public boolean visitIdleMessage(IdleMessage message) {
        Map<List<PeerInterface>, List<Integer>> peersNBlocks = new HashMap<>();
        for(int i = 0; i < peer.totalBlocksCount; ++i){
            if(this.peer.data[i] == null){
                int dataCounter = 0;
                List<PeerInterface> peers = new ArrayList<>();
                List<Integer> indexOfDataNDataCounter = new ArrayList<>();
                indexOfDataNDataCounter.add(i);
                for(var entry : this.peer.peers2BlocksMap.entrySet()){
                    if(this.peer.peers2BlocksMap.get(entry.getKey())[i]){
                        dataCounter++;
                        peers.add(entry.getKey());
                    }
                }
                indexOfDataNDataCounter.add(dataCounter);
                peersNBlocks.put(peers, indexOfDataNDataCounter);
            }
        }
        Entry<List<PeerInterface>, List<Integer>> min = null;
        for (Entry<List<PeerInterface>, List<Integer>> entry : peersNBlocks.entrySet()) {
            if (min == null || min.getValue().get(1) > entry.getValue().get(1)) {
                min = entry;
            }
        }
        assert min != null;
        min.getKey().get(0).request(this.peer, min.getValue().get(0));
        return false;
    }
}
