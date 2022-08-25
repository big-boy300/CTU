package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "person")
@Inheritance(strategy = InheritanceType.JOINED)
public class PersonEntity {
    @Basic
    @Column(name = "passport")
    private String passport;
    @Id
    @Column(name = "langschoolcardnumber")
    private String langschoolcardnumber;
    @Basic
    @Column(name = "name")
    private String name;
    @Basic
    @Column(name = "street")
    private String street;
    @Basic
    @Column(name = "email")
    private String email;
    @Basic
    @Column(name = "dtype")
    private String dtype;
    @OneToOne(mappedBy = "personByStudentid")
    private InvitationEntity invitationByLangschoolcardnumber;
    @OneToMany(mappedBy = "personByFriendid")
    private Collection<InvitationEntity> invitationsByLangschoolcardnumber;
    @OneToMany(mappedBy = "personByPersonid")
    private Collection<LanguageschoolEntity> languageschoolsByLangschoolcardnumber;
    @OneToMany(mappedBy = "personByPersonid_0")
    private Collection<LanguageschoolEntity> languageschoolsByLangschoolcardnumber_0;
    @OneToMany(mappedBy = "personByStudentid")
    private Collection<LessonEntity> lessonsByLangschoolcardnumber;
    @OneToMany(mappedBy = "personByStudentid")
    private Collection<PaymentEntity> paymentsByLangschoolcardnumber;
    @OneToMany(mappedBy = "personByEmployeeid")
    private Collection<PaymentcontrolEntity> paymentcontrolsByLangschoolcardnumber;
    @OneToOne(mappedBy = "personByStudentid")
    private StudentaccountownershipEntity studentaccountownershipByLangschoolcardnumber;
    @OneToMany(mappedBy = "personByTeacherid")
    private Collection<StudygroupEntity> studygroupsByLangschoolcardnumber;
    @OneToMany(mappedBy = "personByEmployeeid")
    private Collection<StudygroupcreationEntity> studygroupcreationsByLangschoolcardnumber;
    @OneToOne(mappedBy = "personByTeacherid")
    private TeacheraccountownershipEntity teacheraccountownershipByLangschoolcardnumber;

    public String getPassport() {
        return passport;
    }

    public void setPassport(String passport) {
        this.passport = passport;
    }

    public String getLangschoolcardnumber() {
        return langschoolcardnumber;
    }

    public void setLangschoolcardnumber(String langschoolcardnumber) {
        this.langschoolcardnumber = langschoolcardnumber;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getDtype() {
        return dtype;
    }

    public void setDtype(String dtype) {
        this.dtype = dtype;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        PersonEntity that = (PersonEntity) o;

        if (passport != null ? !passport.equals(that.passport) : that.passport != null) return false;
        if (langschoolcardnumber != null ? !langschoolcardnumber.equals(that.langschoolcardnumber) : that.langschoolcardnumber != null)
            return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (street != null ? !street.equals(that.street) : that.street != null) return false;
        if (email != null ? !email.equals(that.email) : that.email != null) return false;
        if (dtype != null ? !dtype.equals(that.dtype) : that.dtype != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = passport != null ? passport.hashCode() : 0;
        result = 31 * result + (langschoolcardnumber != null ? langschoolcardnumber.hashCode() : 0);
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (street != null ? street.hashCode() : 0);
        result = 31 * result + (email != null ? email.hashCode() : 0);
        result = 31 * result + (dtype != null ? dtype.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        return "PersonEntity{" +
                "passport='" + passport + '\'' +
                ", langschoolcardnumber='" + langschoolcardnumber + '\'' +
                ", name='" + name + '\'' +
                ", street='" + street + '\'' +
                ", email='" + email + '\'' +
                '}';
    }
}
