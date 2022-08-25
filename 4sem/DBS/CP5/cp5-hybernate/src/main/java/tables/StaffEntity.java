package tables;

import javax.persistence.*;
import java.util.Collection;

@Entity
@Table(name = "staff")
public class StaffEntity extends PersonEntity {
    @Basic
    @Column(name = "position")
    private String position;
    @OneToMany(mappedBy = "staffByEmployeeid")
    private Collection<PaymentcontrolEntity> paymentcontrolsByLangschoolcardnumber;

    @OneToMany(mappedBy = "staffByEmployeeid")
    private Collection<StudygroupcreationEntity> studygroupcreationsByLangschoolcardnumber;

}
