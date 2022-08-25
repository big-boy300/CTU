package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "studentaccount", schema = "public", catalog = "danilrom")
public class StudentaccountEntity {
    @Id
    @Column(name = "login")
    private String login;
    @OneToMany(mappedBy = "studentaccountByAccount")
    private Collection<StudentaccountownershipEntity> studentaccountownershipsByLogin;
    @OneToMany(mappedBy = "studentaccountByAccount_0")
    private Collection<StudentaccountownershipEntity> studentaccountownershipsByLogin_0;
    @OneToMany(mappedBy = "studentaccountByStudentaccount")
    private Collection<WebsiteEntity> websitesByLogin;
    @OneToMany(mappedBy = "studentaccountByStudentaccount_0")
    private Collection<WebsiteEntity> websitesByLogin_0;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        StudentaccountEntity that = (StudentaccountEntity) o;

        if (login != null ? !login.equals(that.login) : that.login != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        return login != null ? login.hashCode() : 0;
    }

    @Override
    public String toString() {
        return "StudentaccountEntity{" +
                "login='" + login + '\'' +
                '}';
    }
}
