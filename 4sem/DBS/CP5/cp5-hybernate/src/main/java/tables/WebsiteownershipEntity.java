package tables;

import javax.persistence.*;

@Entity
@Table(name = "websiteownership", schema = "public", catalog = "danilrom")
public class WebsiteownershipEntity {
    @Basic
    @Column(name = "school")
    private String school;
    @Id
    @Column(name = "domain")
    private String domain;
    @ManyToOne
    @JoinColumn(name = "school", referencedColumnName = "name", nullable = false, insertable = false, updatable = false)
    private LanguageschoolEntity languageschoolBySchool;
    @ManyToOne
    @JoinColumn(name = "school", referencedColumnName = "name", nullable = false, insertable = false, updatable = false)
    private LanguageschoolEntity languageschoolBySchool_0;
    @OneToOne
    @JoinColumn(name = "domain", referencedColumnName = "domain", nullable = false, insertable = false, updatable = false)
    private WebsiteEntity websiteByDomain;
    @OneToOne
    @JoinColumn(name = "domain", referencedColumnName = "domain", nullable = false, insertable = false, updatable = false)
    private WebsiteEntity websiteByDomain_0;

    public String getSchool() {
        return school;
    }

    public void setSchool(String school) {
        this.school = school;
    }

    public String getDomain() {
        return domain;
    }

    public void setDomain(String domain) {
        this.domain = domain;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        WebsiteownershipEntity that = (WebsiteownershipEntity) o;

        if (school != null ? !school.equals(that.school) : that.school != null) return false;
        if (domain != null ? !domain.equals(that.domain) : that.domain != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = school != null ? school.hashCode() : 0;
        result = 31 * result + (domain != null ? domain.hashCode() : 0);
        return result;
    }
}
