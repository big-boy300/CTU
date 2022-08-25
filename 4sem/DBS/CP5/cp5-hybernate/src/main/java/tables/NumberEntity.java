package tables;

import javax.persistence.*;

@Entity
@Table(name = "number", schema = "public", catalog = "danilrom")
public class NumberEntity {
    @Id
    @Column(name = "name")
    private String name;
    @Basic
    @Column(name = "fax")
    private String fax;
    @Basic
    @Column(name = "phone")
    private String phone;
    @OneToOne
    @JoinColumn(name = "name", referencedColumnName = "name", nullable = false, insertable = false, updatable = false)
    private LanguageschoolEntity languageschoolByName;
    @OneToOne
    @JoinColumn(name = "name", referencedColumnName = "name", nullable = false, insertable = false, updatable = false)
    private LanguageschoolEntity languageschoolByName_0;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getFax() {
        return fax;
    }

    public void setFax(String fax) {
        this.fax = fax;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        NumberEntity that = (NumberEntity) o;

        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (fax != null ? !fax.equals(that.fax) : that.fax != null) return false;
        if (phone != null ? !phone.equals(that.phone) : that.phone != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + (fax != null ? fax.hashCode() : 0);
        result = 31 * result + (phone != null ? phone.hashCode() : 0);
        return result;
    }
}
