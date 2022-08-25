package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "payment", schema = "public", catalog = "danilrom")
@IdClass(PaymentEntityPK.class)
public class PaymentEntity {
    @Id
    @Column(name = "studentid")
    private String studentid;
    @Id
    @Column(name = "number")
    private String number;
    @Basic
    @Column(name = "method")
    private String method;
    @ManyToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByStudentid;
    @ManyToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private StudentEntity studentByStudentid;
    @OneToMany(mappedBy = "paymentByFkPaymentcontrolStudentid")
    private Collection<PaymentcontrolEntity> paymentcontrols;
    @OneToMany(mappedBy = "paymentByPaymentcontrolFkPayment")
    private Collection<PaymentcontrolEntity> paymentcontrols_0;

    public String getStudentid() {
        return studentid;
    }

    public void setStudentid(String studentid) {
        this.studentid = studentid;
    }

    public String getNumber() {
        return number;
    }

    public void setNumber(String number) {
        this.number = number;
    }

    public String getMethod() {
        return method;
    }

    public void setMethod(String method) {
        this.method = method;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        PaymentEntity that = (PaymentEntity) o;

        if (studentid != null ? !studentid.equals(that.studentid) : that.studentid != null) return false;
        if (number != null ? !number.equals(that.number) : that.number != null) return false;
        if (method != null ? !method.equals(that.method) : that.method != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = studentid != null ? studentid.hashCode() : 0;
        result = 31 * result + (number != null ? number.hashCode() : 0);
        result = 31 * result + (method != null ? method.hashCode() : 0);
        return result;
    }

    public PersonEntity getPersonByStudentid() {
        return personByStudentid;
    }

    public void setPersonByStudentid(PersonEntity personByStudentid) {
        this.personByStudentid = personByStudentid;
    }

    public StudentEntity getStudentByStudentid() {
        return studentByStudentid;
    }

    public void setStudentByStudentid(StudentEntity studentByStudentid) {
        this.studentByStudentid = studentByStudentid;
    }

    public Collection<PaymentcontrolEntity> getPaymentcontrols() {
        return paymentcontrols;
    }

    public void setPaymentcontrols(Collection<PaymentcontrolEntity> paymentcontrols) {
        this.paymentcontrols = paymentcontrols;
    }

    public Collection<PaymentcontrolEntity> getPaymentcontrols_0() {
        return paymentcontrols_0;
    }

    public void setPaymentcontrols_0(Collection<PaymentcontrolEntity> paymentcontrols_0) {
        this.paymentcontrols_0 = paymentcontrols_0;
    }

    @Override
    public String toString() {
        return "PaymentEntity{" +
                "studentid='" + studentid + '\'' +
                ", number='" + number + '\'' +
                ", method='" + method + '\'' +
                '}';
    }
}
