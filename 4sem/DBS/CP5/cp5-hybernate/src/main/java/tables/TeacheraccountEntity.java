package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "teacheraccount", schema = "public", catalog = "danilrom")
public class TeacheraccountEntity {
    @Id
    @Column(name = "login")
    private String login;
    @OneToMany(mappedBy = "teacheraccountByAccount")
    private Collection<TeacheraccountownershipEntity> teacheraccountownershipsByLogin;
    @OneToMany(mappedBy = "teacheraccountByAccount_0")
    private Collection<TeacheraccountownershipEntity> teacheraccountownershipsByLogin_0;
    @OneToMany(mappedBy = "teacheraccountByTeacheraccount")
    private Collection<WebsiteEntity> websitesByLogin;
    @OneToMany(mappedBy = "teacheraccountByTeacheraccount_0")
    private Collection<WebsiteEntity> websitesByLogin_0;

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        TeacheraccountEntity that = (TeacheraccountEntity) o;

        if (login != null ? !login.equals(that.login) : that.login != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        return login != null ? login.hashCode() : 0;
    }

    public Collection<TeacheraccountownershipEntity> getTeacheraccountownershipsByLogin() {
        return teacheraccountownershipsByLogin;
    }

    public void setTeacheraccountownershipsByLogin(Collection<TeacheraccountownershipEntity> teacheraccountownershipsByLogin) {
        this.teacheraccountownershipsByLogin = teacheraccountownershipsByLogin;
    }

    public Collection<TeacheraccountownershipEntity> getTeacheraccountownershipsByLogin_0() {
        return teacheraccountownershipsByLogin_0;
    }

    public void setTeacheraccountownershipsByLogin_0(Collection<TeacheraccountownershipEntity> teacheraccountownershipsByLogin_0) {
        this.teacheraccountownershipsByLogin_0 = teacheraccountownershipsByLogin_0;
    }

    public Collection<WebsiteEntity> getWebsitesByLogin() {
        return websitesByLogin;
    }

    public void setWebsitesByLogin(Collection<WebsiteEntity> websitesByLogin) {
        this.websitesByLogin = websitesByLogin;
    }

    public Collection<WebsiteEntity> getWebsitesByLogin_0() {
        return websitesByLogin_0;
    }

    public void setWebsitesByLogin_0(Collection<WebsiteEntity> websitesByLogin_0) {
        this.websitesByLogin_0 = websitesByLogin_0;
    }
}
