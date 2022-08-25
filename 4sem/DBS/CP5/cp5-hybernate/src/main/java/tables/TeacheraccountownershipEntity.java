package tables;

import javax.persistence.*;

@Entity
@Table(name = "teacheraccountownership", schema = "public", catalog = "danilrom")
public class TeacheraccountownershipEntity {
    @Id
    @Column(name = "teacherid")
    private String teacherid;
    @Basic
    @Column(name = "account")
    private String account;
    @OneToOne
    @JoinColumn(name = "teacherid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByTeacherid;
    @OneToOne
    @JoinColumn(name = "teacherid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private TeacherEntity teacherByTeacherid;
    @ManyToOne
    @JoinColumn(name = "account", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private TeacheraccountEntity teacheraccountByAccount;
    @ManyToOne
    @JoinColumn(name = "account", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private TeacheraccountEntity teacheraccountByAccount_0;

    public String getTeacherid() {
        return teacherid;
    }

    public void setTeacherid(String teacherid) {
        this.teacherid = teacherid;
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

        TeacheraccountownershipEntity that = (TeacheraccountownershipEntity) o;

        if (teacherid != null ? !teacherid.equals(that.teacherid) : that.teacherid != null) return false;
        if (account != null ? !account.equals(that.account) : that.account != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = teacherid != null ? teacherid.hashCode() : 0;
        result = 31 * result + (account != null ? account.hashCode() : 0);
        return result;
    }

}
