
import java.util.function.BinaryOperator;

public class Calculate<T extends Number> {
    BinaryOperator<T> addOp;
    BinaryOperator<T> minusOp;
    BinaryOperator<T> multiOp;
    BinaryOperator<T> divideOp;

    public Calculate() {
        this.addOp = (x, y) -> {
            if (x instanceof Integer) return (T) Integer.valueOf(x.intValue() + y.intValue());
            if (x instanceof Double) return (T) Double.valueOf(x.doubleValue() + y.doubleValue());
            throw new UnsupportedOperationException("Type is not supported");
        };

        this.minusOp = (x, y) -> {
            if (x instanceof Integer) return (T) Integer.valueOf(x.intValue() - y.intValue());
            if (x instanceof Double) return (T) Double.valueOf(x.doubleValue() - y.doubleValue());
            throw new UnsupportedOperationException("Type is not supported");
        };

        this.multiOp = (x, y) -> {
            if (x instanceof Integer) return (T) Integer.valueOf(x.intValue() * y.intValue());
            if (x instanceof Double) return (T) Double.valueOf(x.doubleValue() * y.doubleValue());
            throw new UnsupportedOperationException("Type is not supported");
        };

        this.divideOp = (x, y) -> {
            if (x instanceof Integer) return (T) Integer.valueOf(x.intValue() / y.intValue());
            if (x instanceof Double) return (T) Double.valueOf(x.doubleValue() / y.doubleValue());
            throw new UnsupportedOperationException("Type is not supported");
        };
    }

    public T add(T a, T b) {
        return this.addOp.apply(a, b);
    }

    public T minus(T a, T b) {
        return this.minusOp.apply(a, b);
    }

    public T multi(T a, T b) {
        return this.multiOp.apply(a, b);
    }
    
    public T divide(T a, T b) {
        return this.divideOp.apply(a, b);
    }

}
