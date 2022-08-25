package tables;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.io.Serializable;

public class PaymentcontrolEntityPK implements Serializable {
    @Column(name = "employeeid")
    @Id
    private String employeeid;
    @Column(name = "payment")
    @Id
    private String payment;

    public String getEmployeeid() {
        return employeeid;
    }

    public void setEmployeeid(String employeeid) {
        this.employeeid = employeeid;
    }

    public String getPayment() {
        return payment;
    }

    public void setPayment(String payment) {
        this.payment = payment;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        PaymentcontrolEntityPK that = (PaymentcontrolEntityPK) o;

        if (employeeid != null ? !employeeid.equals(that.employeeid) : that.employeeid != null) return false;
        if (payment != null ? !payment.equals(that.payment) : that.payment != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = employeeid != null ? employeeid.hashCode() : 0;
        result = 31 * result + (payment != null ? payment.hashCode() : 0);
        return result;
    }
}
