package tables;

import javax.persistence.*;

@Entity
@Table(name = "invitation", schema = "public", catalog = "danilrom")
public class InvitationEntity {
    @Id
    @Column(name = "studentid")
    private String studentid;
    @Basic
    @Column(name = "friendid")
    private String friendid;
    @OneToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByStudentid;
    @OneToOne
    @JoinColumn(name = "studentid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private StudentEntity studentByStudentid;
    @ManyToOne
    @JoinColumn(name = "friendid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private PersonEntity personByFriendid;
    @ManyToOne
    @JoinColumn(name = "friendid", referencedColumnName = "langschoolcardnumber", nullable = false, insertable = false, updatable = false)
    private StudentEntity studentByFriendid;

    public String getStudentid() {
        return studentid;
    }

    public void setStudentid(String studentid) {
        this.studentid = studentid;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        InvitationEntity that = (InvitationEntity) o;

        if (studentid != null ? !studentid.equals(that.studentid) : that.studentid != null) return false;
        if (friendid != null ? !friendid.equals(that.friendid) : that.friendid != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = studentid != null ? studentid.hashCode() : 0;
        result = 31 * result + (friendid != null ? friendid.hashCode() : 0);
        return result;
    }

}
