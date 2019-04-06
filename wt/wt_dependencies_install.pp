# This is the puppet installations manifest for Wt.

package { 'witty':
  ensure => present,
}

package { 'witty-dev':
  ensure => present,
}

package { 'witty-doc':
  ensure => present,
}

package { 'witty-dbg':
  ensure => present,
}

package { 'witty-examples':
  ensure => present,
}


