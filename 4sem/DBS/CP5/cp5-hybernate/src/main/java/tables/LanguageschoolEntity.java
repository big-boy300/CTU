package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "languageschool", schema = "public", catalog = "danilrom")
public class LanguageschoolEntity {
    @Id
    @Column(name = "name")
    private String name;
    @Basic
    @Column(name = "street")
    private String street;
    @Basic
    @Column(name = "email")
    private String email;
    @Basic
    @Column(name = "postalcode")
    private String postalcode;
    @Basic
    @Column(name = "personid")
    private String personid;
    @ManyToOne
    @JoinColumn(name = "personid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByPersonid;
    @ManyToOne
    @JoinColumn(name = "personid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByPersonid_0;
    @OneToOne(mappedBy = "languageschoolByName")
    private NumberEntity numberByName;
    @OneToOne(mappedBy = "languageschoolByName_0")
    private NumberEntity numberByName_0;
    @OneToMany(mappedBy = "languageschoolBySchool")
    private Collection<WebsiteownershipEntity> websiteownershipsByName;
    @OneToMany(mappedBy = "languageschoolBySchool_0")
    private Collection<WebsiteownershipEntity> websiteownershipsByName_0;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        LanguageschoolEntity that = (LanguageschoolEntity) o;

        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (street != null ? !street.equals(that.street) : that.street != null) return false;
        if (email != null ? !email.equals(that.email) : that.email != null) return false;
        if (postalcode != null ? !postalcode.equals(that.postalcode) : that.postalcode != null) return false;
        if (personid != null ? !personid.equals(that.personid) : that.personid != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + (street != null ? street.hashCode() : 0);
        result = 31 * result + (email != null ? email.hashCode() : 0);
        result = 31 * result + (postalcode != null ? postalcode.hashCode() : 0);
        result = 31 * result + (personid != null ? personid.hashCode() : 0);
        return result;
    }

}
