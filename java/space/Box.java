public class Box<T> {
    private final T item;
    public Box(T item) {
        this.item = item;
    }

    public T getItem() {
        return this.item;
    }
}
