package tables;

import javax.persistence.*;

@Entity
@Table(name = "website", schema = "public", catalog = "danilrom")
public class WebsiteEntity {
    @Id
    @Column(name = "domain")
    private String domain;
    @Basic
    @Column(name = "teacheraccount")
    private String teacheraccount;
    @Basic
    @Column(name = "studentaccount")
    private String studentaccount;
    @ManyToOne
    @JoinColumn(name = "teacheraccount", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private TeacheraccountEntity teacheraccountByTeacheraccount;
    @ManyToOne
    @JoinColumn(name = "teacheraccount", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private TeacheraccountEntity teacheraccountByTeacheraccount_0;
    @ManyToOne
    @JoinColumn(name = "studentaccount", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private StudentaccountEntity studentaccountByStudentaccount;
    @ManyToOne
    @JoinColumn(name = "studentaccount", referencedColumnName = "login", nullable = false, insertable = false, updatable = false)
    private StudentaccountEntity studentaccountByStudentaccount_0;
    @OneToOne(mappedBy = "websiteByDomain")
    private WebsiteownershipEntity websiteownershipByDomain;
    @OneToOne(mappedBy = "websiteByDomain_0")
    private WebsiteownershipEntity websiteownershipByDomain_0;

    public String getDomain() {
        return domain;
    }

    public void setDomain(String domain) {
        this.domain = domain;
    }

    public String getTeacheraccount() {
        return teacheraccount;
    }

    public void setTeacheraccount(String teacheraccount) {
        this.teacheraccount = teacheraccount;
    }

    public String getStudentaccount() {
        return studentaccount;
    }

    public void setStudentaccount(String studentaccount) {
        this.studentaccount = studentaccount;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        WebsiteEntity that = (WebsiteEntity) o;

        if (domain != null ? !domain.equals(that.domain) : that.domain != null) return false;
        if (teacheraccount != null ? !teacheraccount.equals(that.teacheraccount) : that.teacheraccount != null)
            return false;
        if (studentaccount != null ? !studentaccount.equals(that.studentaccount) : that.studentaccount != null)
            return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = domain != null ? domain.hashCode() : 0;
        result = 31 * result + (teacheraccount != null ? teacheraccount.hashCode() : 0);
        result = 31 * result + (studentaccount != null ? studentaccount.hashCode() : 0);
        return result;
    }

}
