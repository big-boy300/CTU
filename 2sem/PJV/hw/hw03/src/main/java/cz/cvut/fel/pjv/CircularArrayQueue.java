package cz.cvut.fel.pjv;

/**
 * Implementation of the {@link Queue} backed by fixed size array.
 */
public class CircularArrayQueue implements Queue {

    String[] queue;

    private int const_capacity = 5;
    private int cur_capacity;

    private int head_idx = 0;
    private int tail_idx = 0;

    private int q_size = 0;

    /**
     * Creates the queue with capacity set to the value of 5.
     */
    public CircularArrayQueue() {
        queue = new String[const_capacity];
    }

    /**
     * Creates the queue with given {@code capacity}. The capacity represents maximal number of elements that the
     * queue is able to store.
     *
     * @param capacity of the queue
     */
    public CircularArrayQueue(int capacity) {
        this.cur_capacity = capacity;
        queue = new String[cur_capacity];
    }

    @Override
    public int size() {
        return q_size;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean isFull() {
        int counter = 0;

        for (int i = 0; i < queue.length; ++i) {
            if (queue[i] != null) {
                counter++;
            }
        }

        return counter == queue.length;
    }

    @Override
    public boolean enqueue(String obj) {
        if (isFull() || obj == null) {
            return false;
        } else {
            tail_idx = tail_idx % cur_capacity;
            queue[tail_idx] = obj;
            tail_idx++;
            q_size++;
            return true;
        }
    }

    @Override
    public String dequeue() {
        if (isEmpty()) {
            return null;
        } else {
            head_idx = head_idx % cur_capacity;
            String ret = queue[head_idx];
            queue[head_idx] = null;
            head_idx++;
            q_size--;
            return ret;
        }
    }

    @Override
    public void printAllElements() {
        for (int i = head_idx; i != tail_idx; ++i) {
            System.out.println(queue[i]);
        }
    }
}
