package tables;

import javax.persistence.*;

@Entity
@Table(name = "studentaccountownership", schema = "public", catalog = "danilrom")
public class StudentaccountownershipEntity {
    @Id
    @Column(name = "studentid")
    private String studentid;
    @Basic
    @Column(name = "account")
    private String account;
    @OneToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByStudentid;
    @OneToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private StudentEntity studentByStudentid;
    @ManyToOne
    @JoinColumn(name = "account", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private StudentaccountEntity studentaccountByAccount;
    @ManyToOne
    @JoinColumn(name = "account", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private StudentaccountEntity studentaccountByAccount_0;

    public String getStudentid() {
        return studentid;
    }

    public void setStudentid(String studentid) {
        this.studentid = studentid;
    }

    public String getAccount() {
        return account;
    }

    public void setAccount(String account) {
        this.account = account;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        StudentaccountownershipEntity that = (StudentaccountownershipEntity) o;

        if (studentid != null ? !studentid.equals(that.studentid) : that.studentid != null) return false;
        if (account != null ? !account.equals(that.account) : that.account != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = studentid != null ? studentid.hashCode() : 0;
        result = 31 * result + (account != null ? account.hashCode() : 0);
        return result;
    }

}
