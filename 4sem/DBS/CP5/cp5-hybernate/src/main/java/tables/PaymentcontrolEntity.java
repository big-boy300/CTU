package tables;

import javax.persistence.*;

@Entity
@Table(name = "paymentcontrol", schema = "public", catalog = "danilrom")
@IdClass(PaymentcontrolEntityPK.class)
public class PaymentcontrolEntity {
    @Id
    @Column(name = "employeeid")
    private String employeeid;
    @Id
    @Column(name = "payment")
    private String payment;
    @Basic
    @Column(name = "studentid")
    private String studentid;
    @ManyToOne
    @JoinColumn(name = "employeeid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByEmployeeid;
    @ManyToOne
    @JoinColumn(name = "employeeid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private StaffEntity staffByEmployeeid;
    @ManyToOne
    @JoinColumns({@JoinColumn(name = "studentid", referencedColumnName = "studentid", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "payment", referencedColumnName = "number", nullable = false, insertable = false, updatable = false)})
    private PaymentEntity paymentByFkPaymentcontrolStudentid;
    @ManyToOne
    @JoinColumns({@JoinColumn(name = "studentid", referencedColumnName = "studentid", nullable = false, insertable = false, updatable = false), @JoinColumn(name = "payment", referencedColumnName = "number", nullable = false, insertable = false, updatable = false)})
    private PaymentEntity paymentByPaymentcontrolFkPayment;

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

    public String getStudentid() {
        return studentid;
    }

    public void setStudentid(String studentid) {
        this.studentid = studentid;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        PaymentcontrolEntity that = (PaymentcontrolEntity) o;

        if (employeeid != null ? !employeeid.equals(that.employeeid) : that.employeeid != null) return false;
        if (payment != null ? !payment.equals(that.payment) : that.payment != null) return false;
        if (studentid != null ? !studentid.equals(that.studentid) : that.studentid != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = employeeid != null ? employeeid.hashCode() : 0;
        result = 31 * result + (payment != null ? payment.hashCode() : 0);
        result = 31 * result + (studentid != null ? studentid.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "PaymentcontrolEntity{" +
                "employeeid='" + employeeid + '\'' +
                ", payment='" + payment + '\'' +
                ", studentid='" + studentid + '\'' +
                '}';
    }
}
